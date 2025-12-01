#include "caw/res/icons.h"
#include "caw/logcategory.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_properties.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>

#define QOI_MALLOC(sz) SDL_malloc(sz)
#define QOI_FREE(p)    SDL_free(p)
#define QOI_ZEROARR(a) SDL_zeroa(a)
#define QOI_NO_STDIO

#define QOI_IMPLEMENTATION
#include "qoi.h"

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

	int size;
	const void *data = icon_data(name, &size);
	if (data == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_ICONS, "Icon not found: %s", name);
		return nullptr;
	}

	qoi_desc desc;
	void *pixels = qoi_decode(data, size, &desc, 4);
	if (pixels == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_ICONS, "Failed to load icon: %s", name);
		return nullptr;
	}

	SDL_Surface *surface = SDL_CreateSurfaceFrom((int) desc.width, (int) desc.height,
		SDL_PIXELFORMAT_RGBA32, pixels, (int) (desc.width * desc.channels));
	if (surface == nullptr)
	{
		SDL_free(pixels);
		SDL_LogError(LOG_CATEGORY_ICONS, "Failed to parse icon: %s", SDL_GetError());
		return nullptr;
	}

	SDL_free(pixels);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_ICONS, "Failed to create icon: %s", SDL_GetError());
		SDL_DestroySurface(surface);
		return nullptr;
	}

	SDL_DestroySurface(surface);

	SDL_SetPointerPropertyWithCleanup(props, name, texture, cleanup, nullptr);
	return texture;
}
