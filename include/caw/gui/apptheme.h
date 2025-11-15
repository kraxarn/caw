#pragma once

#include "clay.h"

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
	COLOR_WINDOW_BACKGROUND  = COLOR5,
	COLOR_WINDOW_HEADER      = COLOR4,
	COLOR_WINDOW_BORDER      = COLOR6,
	COLOR_CONTROL_BACKGROUND = COLOR6,
	COLOR_CONTROL_HOVER      = COLOR4,
	COLOR_CONTROL_ACTIVE     = COLOR5,
	COLOR_CONTROL_CURSOR     = COLOR2,
	COLOR_CLEAR              = COLOR6,
	COLOR_BORDER             = COLOR6,

	COLOR_INVALID = 0xff'00'ff,
} app_color_t;

typedef enum app_size_t: Uint8
{
	FONT_SIZE_BODY  = 12,
	FONT_SIZE_TITLE = 16,

	GAP_DEFAULT     = 5,
	GAP_MENUBAR     = 25,
	GAP_WINDOW_ITEM = 15,

	CORNER_RADIUS_DEFAULT = 4,
	CORNER_RADIUS_WINDOW  = 10,
	CORNER_RADIUS_CONTROL = 6,

	PADDING_MENUBAR         = 10,
	PADDING_MENU_ITEM       = 10,
	PADDING_WINDOW_HEADER_Y = 8,
	PADDING_WINDOW_HEADER_X = 12,
	PADDING_WINDOW_CONTENT  = 15,
	PADDING_CONTROL         = 6,
	PADDING_COMBOBOX        = 8,

	WIDTH_COMBOBOX = 175,

	HEIGHT_COMBOBOX = 21 + (PADDING_CONTROL * 2),
} app_size_t;

SDL_Color app_color_sdl(app_color_t color);

Clay_Color app_color_clay(app_color_t color);
