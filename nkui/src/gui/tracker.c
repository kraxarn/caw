#include "caw/gui/tracker.h"
#include "caw/appstate.h"
#include "caw/ui.h"
#include "caw/gui/menubar.h"

void draw_tracker(const app_state_t *state)
{
	draw_menubar(state);

	const nk_bool visible = nk_begin(state->ctx, "UI",
		nk_rect(50, 50, 220, 220),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE
	);

	if (!visible)
	{
		nk_end(state->ctx);
		return;
	}

	nk_layout_row_static(state->ctx, 30, 80, 1);

	if (nk_button_label(state->ctx, "button"))
	{
	}

	nk_end(state->ctx);
}
