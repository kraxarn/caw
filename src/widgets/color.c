#include "shiny/color.h"
#include "shiny/internal/color.h"
#include "shiny/theme.h"
#include "shiny/themekey.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>

Uint8 red(const shiny_color_t color)
{
	return (Uint8) (color >> 16);
}

Uint8 green(const shiny_color_t color)
{
	return (Uint8) (color >> 8);
}

Uint8 blue(const shiny_color_t color)
{
	return (Uint8) color;
}

Clay_Color shiny_clay_color(const shiny_color_t color)
{
	return (Clay_Color){
		.r = red(color),
		.g = green(color),
		.b = blue(color),
		.a = SDL_ALPHA_OPAQUE,
	};
}

Clay_Color shiny_clay_theme_color(const shiny_theme_color_t color)
{
	return shiny_clay_color(shiny_theme_color(color));
}

SDL_Color shiny_sdl_color(shiny_color_t color)
{
	return (SDL_Color){
		.r = red(color),
		.g = green(color),
		.b = blue(color),
		.a = SDL_ALPHA_OPAQUE,
	};
}

SDL_Color shiny_sdl_theme_color(const shiny_theme_color_t color)
{
	return shiny_sdl_color(shiny_theme_color(color));
}
