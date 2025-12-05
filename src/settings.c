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

char *settings_read_file(SDL_Storage *storage)
{
	Uint64 size;
	if (!SDL_GetStorageFileSize(storage, FILENAME, &size))
	{
		return nullptr;
	}

	void *buffer = SDL_malloc(size);
	if (!SDL_ReadStorageFile(storage, FILENAME, buffer, size))
	{
		SDL_free(buffer);
		return nullptr;
	}

	return buffer;
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

bool settings_parse(settings_t *settings)
{
	if (settings->props > 0)
	{
		return true;
	}

	if (!SDL_StorageReady(settings->storage))
	{
		return SDL_SetError("Storage not ready");
	}

	settings->props = SDL_CreateProperties();

	char *content = settings_read_file(settings->storage);
	if (content == nullptr)
	{
		return false;
	}

	const char *current = content;
	while (current != nullptr)
	{
		char *end = SDL_strchr(current, '\n');
		if (end != nullptr)
		{
			*end = '\0';
		}

		char *split = SDL_strchr(current, '=');
		*split = '\0';

		SDL_SetStringProperty(settings->props, current, split + 1);

		current = end == nullptr ? end : end + 1;
	}

	SDL_free(content);
	return true;
}

const char *settings_string(settings_t *settings, const char *key, const char *fallback)
{
	if (!settings_parse(settings))
	{
		return nullptr;
	}
	return SDL_GetStringProperty(settings->props, key, fallback);
}

bool settings_set_string(settings_t *settings, const char *key, const char *value)
{
	if (!settings_parse(settings))
	{
		return false;
	}
	return SDL_SetStringProperty(settings->props, key, value);
}
