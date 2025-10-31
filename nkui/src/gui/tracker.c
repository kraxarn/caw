#include "caw/gui/tracker.h"
#include "caw/ui.h"

void draw_tracker(struct nk_context *ctx)
{
	const nk_bool visible = nk_begin(ctx, "UI",
		nk_rect(50, 50, 220, 220),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE
	);

	if (!visible)
	{
		nk_end(ctx);
		return;
	}

	nk_layout_row_static(ctx, 30, 80, 1);

	if (nk_button_label(ctx, "button"))
	{
	}

	nk_end(ctx);
}
