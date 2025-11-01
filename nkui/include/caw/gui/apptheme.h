#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>

/*
* Oil 6 Palette
* By GrafxKid
* https://lospec.com/palette-list/oil-6
*/

typedef enum app_color_t: Uint32
{
	COLOR1 = 0xfb'f5'ef,
	COLOR2 = 0xf2'd3'ab,
	COLOR3 = 0xc6'9f'a5,
	COLOR4 = 0x8b'6d'9c,
	COLOR5 = 0x49'4d'7e,
	COLOR6 = 0x27'27'44,

	COLOR_FOREGROUND         = COLOR1,
	COLOR_CLEAR              = COLOR4,
	COLOR_WINDOW_BACKGROUND  = COLOR5,
	COLOR_CONTROL_BACKGROUND = COLOR6,
} app_color_t;

SDL_Color app_color_sdl(app_color_t color);
