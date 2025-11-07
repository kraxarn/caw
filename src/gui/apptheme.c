#include "caw/gui/apptheme.h"
#include "caw/ui.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>

Uint8 red(const app_color_t color)
{
	return (Uint8)(color >> 16);
}

Uint8 green(const app_color_t color)
{
	return (Uint8)(color >> 8);
}

Uint8 blue(const app_color_t color)
{
	return (Uint8)color;
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

struct nk_color app_color_nk(const app_color_t color)
{
	return nk_rgb(red(color), green(color), blue(color));
}

void set_style(struct nk_context *ctx)
{
	struct nk_color table[NK_COLOR_COUNT];

	table[NK_COLOR_TEXT] = app_color_nk(COLOR_FOREGROUND);
	table[NK_COLOR_WINDOW] = app_color_nk(COLOR_WINDOW_BACKGROUND);
	table[NK_COLOR_HEADER] = app_color_nk(COLOR_WINDOW_HEADER);
	table[NK_COLOR_BORDER] = app_color_nk(COLOR_WINDOW_BORDER);
	table[NK_COLOR_BUTTON] = app_color_nk(COLOR_CONTROL_BACKGROUND);
	table[NK_COLOR_BUTTON_HOVER] = app_color_nk(COLOR_CONTROL_HOVER);
	table[NK_COLOR_BUTTON_ACTIVE] = app_color_nk(COLOR_CONTROL_ACTIVE);
	table[NK_COLOR_TOGGLE] = app_color_nk(COLOR_CONTROL_BACKGROUND);
	table[NK_COLOR_TOGGLE_HOVER] = app_color_nk(COLOR_CONTROL_HOVER);
	table[NK_COLOR_TOGGLE_CURSOR] = app_color_nk(COLOR_CONTROL_CURSOR);
	table[NK_COLOR_SELECT] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SELECT_ACTIVE] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SLIDER] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SLIDER_CURSOR] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SLIDER_CURSOR_HOVER] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_PROPERTY] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_EDIT] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_EDIT_CURSOR] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_COMBO] = app_color_nk(COLOR_CONTROL_BACKGROUND);
	table[NK_COLOR_CHART] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_CHART_COLOR] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SCROLLBAR] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SCROLLBAR_CURSOR] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_TAB_HEADER] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_KNOB] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_KNOB_CURSOR] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_KNOB_CURSOR_HOVER] = app_color_nk(COLOR_INVALID);
	table[NK_COLOR_KNOB_CURSOR_ACTIVE] = app_color_nk(COLOR_INVALID);

	nk_style_from_table(ctx, table);
}
