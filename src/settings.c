#include "caw/settings.h"

#include "tomlc17.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_storage.h>

#define FILENAME "settings.toml"

typedef struct settings_t
{
	SDL_Storage *storage;
	toml_result_t toml;
	bool loaded;
} settings_t;

SDL_Storage *settings_open_storage()
{
	const char *name = SDL_GetAppMetadataProperty(SDL_PROP_APP_METADATA_NAME_STRING);
	const char *creator = SDL_GetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING);
	return SDL_OpenUserStorage(creator, name, 0);
}

bool settings_read_file(settings_t *settings)
{
	Uint64 size;
	if (!SDL_GetStorageFileSize(settings->storage, FILENAME, &size))
	{
		return false;
	}

	void *buffer = SDL_malloc(size);
	if (!SDL_ReadStorageFile(settings->storage, FILENAME, buffer, size))
	{
		SDL_free(buffer);
		return false;
	}

	toml_option_t options = toml_default_option();
	options.mem_realloc = SDL_realloc;
	options.mem_free = SDL_free;
	toml_set_option(options);

	toml_result_t result = toml_parse(buffer, (int) size);
	SDL_free(buffer);
	if (!result.ok)
	{
		toml_free(result);
		SDL_SetError("TOML error: %s", result.errmsg);
		return false;
	}

	settings->toml = result;
	settings->loaded = true;

	return true;
}

void settings_write_file()
{
	// TODO
}

settings_t *settings_open()
{
	settings_t *settings = SDL_malloc(sizeof(settings_t));
	settings->storage = settings_open_storage();
	settings->loaded = false;
	return settings;
}

void settings_close(settings_t *settings)
{
	toml_free(settings->toml);
	SDL_CloseStorage(settings->storage);
	SDL_free(settings);
}

bool settings_ready(const settings_t *settings)
{
	return SDL_StorageReady(settings->storage);
}

toml_datum_t settings_value(settings_t *settings, const char *key)
{
	if (!SDL_StorageReady(settings->storage))
	{
		return (toml_datum_t){};
	}

	if (!settings->loaded && !settings_read_file(settings))
	{
		return (toml_datum_t){};
	}

	return toml_seek(settings->toml.toptab, key);
}

const char *settings_string(settings_t *settings, const char *key, const char *fallback)
{
	const toml_datum_t value = settings_value(settings, key);
	return value.type == TOML_STRING ? value.u.s : fallback;
}
