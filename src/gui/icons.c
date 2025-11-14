#include "caw/res/icons.h"
#include "caw/logcategory.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_properties.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>

#include "caw/gui/apptheme.h"

static SDL_PropertiesID props = 0;

void cleanup([[maybe_unused]] void *userdata, void *value)
{
	SDL_DestroyTexture(value);
}

// Is there a better way to do this?
void set_color(SDL_Surface *surface, const SDL_Color color)
{
	for (auto x = 0; x < surface->w; x++)
	{
		for (auto y = 0; y < surface->h; y++)
		{
			Uint8 r;
			Uint8 g;
			Uint8 b;
			Uint8 a;

			if (!SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a) || a == 0)
			{
				continue;
			}

			SDL_WriteSurfacePixel(surface, x, y, color.r, color.g, color.b, color.a);
		}
	}
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

	SDL_Surface *surface = IMG_LoadSVG_IO(src);
	if (surface == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_ICONS, "Failed to parse icon: %s", SDL_GetError());
		return nullptr;
	}

	set_color(surface, app_color_sdl(COLOR_FOREGROUND));

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
