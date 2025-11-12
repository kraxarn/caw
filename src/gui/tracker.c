#include "caw/gui/tracker.h"
#include "caw/appstate.h"
#include "caw/gui/apptheme.h"
#include "caw/gui/menubar.h"
#include "caw/gui/windowsettings.h"
#include "caw/renderer/clayrenderersdl3.h"

#include <SDL3/SDL_rect.h>

void menubar()
{
	const Clay_LayoutConfig layout = {
		.layoutDirection = CLAY_LEFT_TO_RIGHT,
		.sizing = (Clay_Sizing){
			.width = CLAY_SIZING_GROW(0),
			.height = CLAY_SIZING_FIXED(0),
		},
		.padding = CLAY_PADDING_ALL(SIZE_MENUBAR_PADDING),
		.childGap = SIZE_MENUBAR_GAP,
	};

	const Clay_ElementDeclaration element = {
		.layout = layout,
		.backgroundColor = app_color_clay(COLOR_WINDOW_BACKGROUND),
	};

	CLAY(CLAY_ID("Menubar"), element)
	{
		const Clay_TextElementConfig text_config = {
			.fontSize = 12,
			.textColor = app_color_clay(COLOR_FOREGROUND),
		};

		CLAY_TEXT(CLAY_STRING("File"), CLAY_TEXT_CONFIG(text_config));
		CLAY_TEXT(CLAY_STRING("View"), CLAY_TEXT_CONFIG(text_config));
		CLAY_TEXT(CLAY_STRING("Debug"), CLAY_TEXT_CONFIG(text_config));
		CLAY_TEXT(CLAY_STRING("Help"), CLAY_TEXT_CONFIG(text_config));
	}
}

void draw_tracker_clay(const app_state_t *state)
{
	const Clay_Padding padding = {
		.left = SIZE_GAP + state->gui.out.safe_area.x,
		.right = SIZE_GAP + (state->gui.out.width - state->gui.out.safe_area.w - state->gui.out.safe_area.x),
		.top = SIZE_GAP + state->gui.out.safe_area.y,
		.bottom = SIZE_GAP + (state->gui.out.height - state->gui.out.safe_area.h - state->gui.out.safe_area.y),
	};

	const Clay_LayoutConfig layout = {
		.layoutDirection = CLAY_TOP_TO_BOTTOM,
		.sizing = (Clay_Sizing){
			.width = CLAY_SIZING_GROW(0),
			.height = CLAY_SIZING_GROW(0),
		},
		.padding = padding,
	};

	const Clay_ElementDeclaration element = {
		.layout = layout,
		.backgroundColor = app_color_clay(COLOR_CLEAR),
	};

	CLAY(CLAY_ID("Container"), element)
	{
		menubar();
	}
}

void draw_tracker(app_state_t *state)
{
	if (state->gui.mode == UI_CLAY)
	{
		return draw_tracker_clay(state);
	}

	draw_menubar(state);

	if (state->gui.windows.settings)
	{
		draw_settings_window(state);
	}
}
