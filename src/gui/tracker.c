#include "caw/gui/tracker.h"
#include "caw/appstate.h"
#include "caw/gui/menubar.h"
#include "caw/gui/windowsettings.h"

#include "shiny/layout.h"

void tracker(app_state_t *state)
{
	constexpr shiny_layout_flag_t flags =
		SHINY_PADDING_DEFAULT
		| SHINY_LAYOUT_TOP_TO_BOTTOM
		| SHINY_SIZE_GROW_X
		| SHINY_SIZE_GROW_Y;

	shiny_layout_begin("Container", flags);
	{
		menubar(state);
	}
	shiny_layout_end();

	if (state->gui.windows.settings.visible)
	{
		settings_window(state);
	}
}
