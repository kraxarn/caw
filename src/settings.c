#include "caw/settings.h"
#include "caw/logcategory.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_properties.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_storage.h>

#define FILENAME "settings.cfg"

typedef struct settings_t
{
	SDL_Storage *storage;
	SDL_PropertiesID props;
} settings_t;

SDL_Storage *settings_open_storage()
{
	const char *name = SDL_GetAppMetadataProperty(SDL_PROP_APP_METADATA_NAME_STRING);
	const char *creator = SDL_GetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING);
	return SDL_OpenUserStorage(creator, name, 0);
}

bool settings_read_file(const settings_t *settings)
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

	SDL_free(buffer);
	return true;
}

void settings_write_callback(void *userdata, const SDL_PropertiesID props, const char *name)
{
	char *line;

	switch (SDL_GetPropertyType(props, name))
	{
		case SDL_PROPERTY_TYPE_STRING:
			SDL_asprintf(&line, "%s=%s", name, SDL_GetStringProperty(props, name, ""));
			break;

		case SDL_PROPERTY_TYPE_NUMBER:
			SDL_asprintf(&line, "%s=%lld", name, SDL_GetNumberProperty(props, name, 0));
			break;

		case SDL_PROPERTY_TYPE_FLOAT:
			SDL_asprintf(&line, "%s=%f", name, SDL_GetFloatProperty(props, name, 0));
			break;

		case SDL_PROPERTY_TYPE_BOOLEAN:
			SDL_asprintf(&line, "%s=%s", name, (int) SDL_GetBooleanProperty(props, name, false) ? "true" : "false");
			break;

		case SDL_PROPERTY_TYPE_INVALID:
		case SDL_PROPERTY_TYPE_POINTER:
			SDL_LogWarn(LOG_CATEGORY_GUI, "Invalid type for '%s', ignoring", name);
			return;
	}

	char *current = *(char **) userdata;
	if (current == nullptr)
	{
		SDL_asprintf((char **) userdata, "%s", line);
	}
	else
	{
		SDL_asprintf((char **) userdata, "%s\n%s", current, line);
		SDL_free(current);
	}

	SDL_free(line);
}

bool settings_write_file(const settings_t *settings)
{
	if (!SDL_StorageReady(settings->storage))
	{
		return SDL_SetError("Failed to write settings, storage not ready");
	}

	char *out = nullptr;

	if (!SDL_EnumerateProperties(settings->props, settings_write_callback, (void *) &out))
	{
		return false;
	}

	if (!SDL_WriteStorageFile(settings->storage, FILENAME, out, SDL_strlen(out)))
	{
		SDL_free(out);
		return false;
	}

	SDL_free(out);
	return true;
}

settings_t *settings_open()
{
	settings_t *settings = SDL_malloc(sizeof(settings_t));
	settings->storage = settings_open_storage();
	settings->props = SDL_CreateProperties();
	return settings;
}

bool settings_flush(const settings_t *settings)
{
	return settings_write_file(settings);
}

void settings_close(settings_t *settings)
{
	SDL_CloseStorage(settings->storage);
	SDL_DestroyProperties(settings->props);
	SDL_free(settings);
}

bool settings_ready(const settings_t *settings)
{
	return SDL_StorageReady(settings->storage);
}

// toml_datum_t settings_value(settings_t *settings, const char *key)
// {
// 	if (!SDL_StorageReady(settings->storage))
// 	{
// 		return (toml_datum_t)
// 		{
// 		};
// 	}
//
// 	if (!settings->loaded && !settings_read_file(settings))
// 	{
// 		return (toml_datum_t)
// 		{
// 		};
// 	}
//
// 	return toml_seek(settings->toml.toptab, key);
// }

bool settings_set_string(const settings_t *settings, const char *key, const char *value)
{
	// const toml_datum_t value = settings_value(settings, key);
	// return value.type == TOML_STRING ? value.u.s : fallback;

	return SDL_SetStringProperty(settings->props, key, value);
}
