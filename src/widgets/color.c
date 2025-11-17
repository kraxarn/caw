#include "shiny/internal/color.h"

#include "clay.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>

Clay_Color shiny_color_rgb(const Uint32 color)
{
	return (Clay_Color){
		.r = (Uint8) (color >> 16),
		.g = (Uint8) (color >> 8),
		.b = (Uint8) color,
		.a = SDL_ALPHA_OPAQUE,
	};
}
