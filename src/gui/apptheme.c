#include "caw/gui/apptheme.h"

#include "clay.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>

Uint8 red(const app_color_t color)
{
	return (Uint8) (color >> 16);
}

Uint8 green(const app_color_t color)
{
	return (Uint8) (color >> 8);
}

Uint8 blue(const app_color_t color)
{
	return (Uint8) color;
}

SDL_Color app_color_sdl(const app_color_t color)
{
	return (SDL_Color){
		.r = red(color),
		.g = green(color),
		.b = blue(color),
		.a = SDL_ALPHA_OPAQUE,
	};
}

Clay_Color app_color_clay(app_color_t color)
{
	return (Clay_Color){
		.r = red(color),
		.g = green(color),
		.b = blue(color),
		.a = SDL_ALPHA_OPAQUE,
	};
}
