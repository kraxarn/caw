#include "caw/gui/tracker.h"
#include "caw/appstate.h"
#include "caw/gui/menubar.h"
#include "caw/gui/windowsettings.h"

void draw_tracker(app_state_t *state)
{
	draw_menubar(state);
	draw_settings_window(state);
}
