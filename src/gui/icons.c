#include "caw/res/icons.h"
#include "caw/logcategory.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_properties.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

static SDL_PropertiesID props = 0;

void cleanup([[maybe_unused]] void *userdata, void *value)
{
	SDL_DestroyTexture(value);
}

SDL_Texture *icon(SDL_Renderer *renderer, const char *name)
{
	if (props == 0)
	{
		props = SDL_CreateProperties();
	}

	if (SDL_HasProperty(props, name))
	{
		return SDL_GetPointerProperty(props, name, nullptr);
	}

	SDL_LogDebug(LOG_CATEGORY_ICONS, "Loading icon: %s", name);

	size_t len = 0;
	const char *data = icon_data(name, &len);
	if (data == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_ICONS, "Icon not found: %s", name);
		return nullptr;
	}

	SDL_IOStream *src = SDL_IOFromConstMem(data, len);
	if (src == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_ICONS, "Failed to load icon: %s", SDL_GetError());
		return nullptr;
	}

	SDL_Texture *tex = IMG_LoadTextureTyped_IO(renderer, src, true, "SVG");
	if (tex == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_ICONS, "Failed to parse icon: %s", SDL_GetError());
		return nullptr;
	}

	SDL_SetPointerPropertyWithCleanup(props, name, tex, cleanup, nullptr);
	return tex;
}
