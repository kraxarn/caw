#include "caw/gui/tracker.h"
#include "caw/appstate.h"
#include "caw/gui/apptheme.h"
#include "caw/gui/menubar.h"
#include "caw/gui/windowsettings.h"

#include "shiny/internal/color.h"

#include <SDL3/SDL_rect.h>

void tracker(app_state_t *state)
{
	const Clay_Padding padding = {
		.left = GAP_DEFAULT + state->gui.out.safe_area.x,
		.right = GAP_DEFAULT + (state->gui.out.width - state->gui.out.safe_area.w - state->gui.out.safe_area.x),
		.top = GAP_DEFAULT + state->gui.out.safe_area.y,
		.bottom = GAP_DEFAULT + (state->gui.out.height - state->gui.out.safe_area.h - state->gui.out.safe_area.y),
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
		.backgroundColor = shiny_color_rgb(COLOR_CLEAR),
	};

	CLAY(CLAY_ID("Container"), element)
	{
		menubar(state);
	}

	if (state->gui.windows.settings.visible)
	{
		settings_window(state);
	}
}
