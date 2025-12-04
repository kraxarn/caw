#include "caw/gui/tracker.h"
#include "caw/appstate.h"
#include "caw/gui/menubar.h"
#include "caw/gui/windowsettings.h"

#include "shiny/theme.h"
#include "shiny/themekey.h"
#include "shiny/internal/color.h"

void tracker(app_state_t *state)
{
	const Clay_Padding padding = {
		.left = shiny_theme_gap(SHINY_GAP_DEFAULT),
		.right = shiny_theme_gap(SHINY_GAP_DEFAULT),
		.top = shiny_theme_gap(SHINY_GAP_DEFAULT),
		.bottom = shiny_theme_gap(SHINY_GAP_DEFAULT),
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
		.backgroundColor = shiny_clay_theme_color(SHINY_COLOR_CLEAR),
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
