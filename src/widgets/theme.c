#include "shiny/theme.h"
#include "shiny/color.h"
#include "shiny/themekey.h"

#include <SDL3/SDL_stdinc.h>

shiny_theme_color_t colors[SHINY_COLOR_SIZE];
shiny_theme_gap_t gaps[SHINY_GAP_SIZE];
shiny_theme_corner_radius_t corner_radiuses[SHINY_CORNER_RADIUS_SIZE];
shiny_theme_padding_t paddings[SHINY_PADDING_SIZE];
shiny_theme_size_t sizes[SHINY_SIZE_SIZE];

shiny_color_t shiny_theme_color(const shiny_theme_color_t key)
{
	return colors[key];
}

void shiny_theme_set_color(const shiny_theme_color_t key, const shiny_color_t value)
{
	colors[key] = value;
}

Uint16 shiny_theme_gap(const shiny_theme_gap_t key)
{
	return gaps[key];
}

void shiny_theme_set_gap(const shiny_theme_gap_t key, const Uint16 value)
{
	gaps[key] = value;
}

float shiny_theme_corner_radius(const shiny_theme_corner_radius_t key)
{
	return corner_radiuses[key];
}

void shiny_theme_set_corner_radius(const shiny_theme_corner_radius_t key, const float value)
{
	corner_radiuses[key] = value;
}

Uint16 shiny_theme_padding(const shiny_theme_padding_t key)
{
	return paddings[key];
}

void shiny_theme_set_padding(const shiny_theme_padding_t key, const Uint16 value)
{
	paddings[key] = value;
}

float shiny_theme_size(const shiny_theme_size_t key)
{
	return sizes[key];
}

void shiny_theme_set_size(const shiny_theme_size_t key, const float value)
{
	sizes[key] = value;
}

void shiny_default_theme()
{
	// Oil 6 Palette by GrafxKid
	// https://lospec.com/palette-list/oil-6

	constexpr shiny_color_t color1 = 0xfb'f5'ef;
	constexpr shiny_color_t color2 = 0xf2'd3'ab;
	constexpr shiny_color_t color3 = 0xc6'9f'a5;
	constexpr shiny_color_t color4 = 0x8b'6d'9c;
	constexpr shiny_color_t color5 = 0x49'4d'7e;
	constexpr shiny_color_t color6 = 0x27'27'44;

	shiny_theme_set_color(SHINY_COLOR_FOREGROUND, color1);
	shiny_theme_set_color(SHINY_COLOR_WINDOW_BACKGROUND, color5);
	shiny_theme_set_color(SHINY_COLOR_WINDOW_HEADER, color4);
	shiny_theme_set_color(SHINY_COLOR_WINDOW_BORDER, color6);
	shiny_theme_set_color(SHINY_COLOR_CONTROL_BACKGROUND, color6);
	shiny_theme_set_color(SHINY_COLOR_CONTROL_HOVER, color4);
	shiny_theme_set_color(SHINY_COLOR_CONTROL_ACTIVE, color5);
	shiny_theme_set_color(SHINY_COLOR_CONTROL_CURSOR, color2);
	shiny_theme_set_color(SHINY_COLOR_CLEAR, color6);
	shiny_theme_set_color(SHINY_COLOR_BORDER, color6);

	shiny_theme_set_gap(SHINY_GAP_DEFAULT, 5);
	shiny_theme_set_gap(SHINY_GAP_MENUBAR, 25);
	shiny_theme_set_gap(SHINY_GAP_WINDOW_ITEM, 15);

	shiny_theme_set_corner_radius(SHINY_CORNER_RADIUS_DEFAULT, 4);
	shiny_theme_set_corner_radius(SHINY_CORNER_RADIUS_WINDOW, 8);
	shiny_theme_set_corner_radius(SHINY_CORNER_RADIUS_CONTROL, 6);

	shiny_theme_set_padding(SHINY_PADDING_MENUBAR, 10);
	shiny_theme_set_padding(SHINY_PADDING_MENU_ITEM, 10);
	shiny_theme_set_padding(SHINY_PADDING_WINDOW_HEADER_Y, 8);
	shiny_theme_set_padding(SHINY_PADDING_WINDOW_HEADER_X, 12);
	shiny_theme_set_padding(SHINY_PADDING_WINDOW_CONTENT, 15);
	shiny_theme_set_padding(SHINY_PADDING_CONTROL, 6);
	shiny_theme_set_padding(SHINY_PADDING_COMBOBOX, 8);

	shiny_theme_set_size(SHINY_WIDTH_COMBOBOX, 175);
	shiny_theme_set_size(SHINY_HEIGHT_COMBOBOX, 21
		+ (shiny_theme_padding(SHINY_PADDING_CONTROL) * 2));
}
