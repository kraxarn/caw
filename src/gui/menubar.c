#include "caw/gui/menubar.h"
#include "caw/appstate.h"
#include "caw/guistate.h"
#include "caw/ui.h"
#include "caw/gui/apptheme.h"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_dialog.h>

void SDLCALL on_file_opened(void *userdata, const char *const *filelist, int filter)
{
}

void draw_file_menu(app_state_t *state)
{
	constexpr auto content_height = 256.F;
	constexpr auto content_width = 160.F;

	if (nk_menu_begin_label(state->ctx, "File", 0, nk_vec2(content_width, content_height)))
	{
		nk_layout_row_dynamic(state->ctx, SIZE_MENU_ITEM_HEIGHT, 1);

		nk_menu_item_label(state->ctx, "New...", NK_TEXT_LEFT);

		if (nk_menu_item_label(state->ctx, "Open...", NK_TEXT_LEFT))
		{
			const SDL_DialogFileFilter filters[] = {
				{"caw project", "caw"},
			};

			SDL_ShowOpenFileDialog(on_file_opened, nullptr, state->window, filters, 1, nullptr,
				false);
		}

		nk_menu_item_label(state->ctx, "Save", NK_TEXT_LEFT);
		nk_menu_item_label(state->ctx, "Save As...", NK_TEXT_LEFT);
		nk_menu_item_label(state->ctx, "Export...", NK_TEXT_LEFT);

		if (nk_menu_item_label(state->ctx, "Quit", NK_TEXT_LEFT))
		{
			state->result = SDL_APP_SUCCESS;
		}

		nk_menu_end(state->ctx);
	}
}

enum nk_symbol_type radio_symbol(const int checked)
{
	return checked
		? NK_SYMBOL_CIRCLE_SOLID
		: NK_SYMBOL_CIRCLE_OUTLINE;
}

void draw_view_menu(app_state_t *state)
{
	constexpr auto content_height = 340.F;
	constexpr auto content_width = 180.F;

	if (nk_menu_begin_label(state->ctx, "View", 0, nk_vec2(content_width, content_height)))
	{
		constexpr auto item_height = 30.F;
		nk_layout_row_dynamic(state->ctx, item_height, 1);

		nk_checkbox_label(state->ctx, "Settings", &state->gui.windows.settings);

		nk_menu_end(state->ctx);
	}
}

void draw_debug_menu(const app_state_t *state)
{
	constexpr auto content_height = 256.F;
	constexpr auto content_width = 160.F;

	if (nk_menu_begin_label(state->ctx, "Debug", 0, nk_vec2(content_width, content_height)))
	{
		nk_layout_row_dynamic(state->ctx, SIZE_MENU_ITEM_HEIGHT, 1);

		nk_menu_end(state->ctx);
	}
}

void draw_help_menu(const app_state_t *state)
{
	constexpr auto content_height = 256.F;
	constexpr auto content_width = 160.F;

	if (nk_menu_begin_label(state->ctx, "Help", 0, nk_vec2(content_width, content_height)))
	{
		nk_layout_row_dynamic(state->ctx, SIZE_MENU_ITEM_HEIGHT, 1);

		nk_menu_item_label(state->ctx, "About...", NK_TEXT_LEFT);

		nk_menu_end(state->ctx);
	}
}

void draw_menubar(app_state_t *state)
{
	const auto rect = nk_rect(
		SIZE_GAP, SIZE_GAP,
		(float) state->gui.out.width - (SIZE_GAP * 2), SIZE_MENUBAR_HEIGHT
	);

	nk_begin(state->ctx, "", rect, NK_WINDOW_BORDER);
	{
		nk_menubar_begin(state->ctx);
		{
			nk_layout_row_begin(state->ctx, NK_STATIC, 0, 4);
			{
				constexpr auto file_width = 50.F;
				constexpr auto view_width = 50.F;
				constexpr auto debug_width = 60.F;
				constexpr auto help_width = 60.F;

				nk_layout_row_push(state->ctx, file_width);
				draw_file_menu(state);

				nk_layout_row_push(state->ctx, view_width);
				draw_view_menu(state);

				nk_layout_row_push(state->ctx, debug_width);
				draw_debug_menu(state);

				nk_layout_row_push(state->ctx, help_width);
				draw_help_menu(state);
			}
			nk_layout_row_end(state->ctx);
		}
		nk_menubar_end(state->ctx);
	}
	nk_end(state->ctx);
}
