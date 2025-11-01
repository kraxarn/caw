#include "caw/gui/menubar.h"
#include "caw/appstate.h"
#include "caw/ui.h"

void draw_menubar(const app_state_t *state)
{
	const auto rect = nk_rect(8.F, 8.F, (float)state->gui.out.width - 16.F, 32.F);
	nk_begin(state->ctx, "", rect, NK_WINDOW_BORDER);
	{
	}
	nk_end(state->ctx);
}
