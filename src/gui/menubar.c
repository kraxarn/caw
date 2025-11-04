#include "caw/gui/menubar.h"
#include "caw/appstate.h"
#include "caw/guistate.h"
#include "caw/ui.h"
#include "caw/gui/apptheme.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_audio.h>

void draw_file_menu(const app_state_t *state)
{
	constexpr auto content_height = 256.F;
	constexpr auto content_width = 160.F;

	if (nk_menu_begin_label(state->ctx, "File", 0, nk_vec2(content_width, content_height)))
	{
		nk_layout_row_dynamic(state->ctx, SIZE_MENU_ITEM_HEIGHT, 1);

		nk_menu_item_label(state->ctx, "New...", NK_TEXT_LEFT);
		nk_menu_item_label(state->ctx, "Open...", NK_TEXT_LEFT);
		nk_menu_item_label(state->ctx, "Save", NK_TEXT_LEFT);
		nk_menu_item_label(state->ctx, "Save As...", NK_TEXT_LEFT);
		nk_menu_item_label(state->ctx, "Export...", NK_TEXT_LEFT);
		nk_menu_item_label(state->ctx, "Quit", NK_TEXT_LEFT);

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

	// gui_settings_state_t *settings = &state->gui.settings;

	if (nk_menu_begin_label(state->ctx, "View", 0, nk_vec2(content_width, content_height)))
	{
		constexpr auto item_height = 30.F;
		nk_layout_row_dynamic(state->ctx, item_height, 1);

		nk_checkbox_label(state->ctx, "Settings", &state->gui.windows.settings);

		// nk_layout_row_dynamic(state->ctx, item_height, 2);
		//
		// nk_label(state->ctx, " Renderer", NK_TEXT_ALIGN_LEFT);
		// nk_label(state->ctx, " Audio driver", NK_TEXT_ALIGN_LEFT);
		//
		// nk_layout_row_dynamic(state->ctx, content_height, 2);

		// if (nk_group_begin(state->ctx, "", 0))
		// {
		// 	nk_layout_row_dynamic(state->ctx, item_height, 1);
		//
		// 	if (nk_button_symbol_label(state->ctx, radio_symbol(settings->renderer == nullptr),
		// 		"auto", NK_TEXT_ALIGN_LEFT))
		// 	{
		// 		settings->renderer = nullptr;
		// 	}
		//
		// 	const auto num = SDL_GetNumRenderDrivers();
		// 	for (auto i = 0; i < num; i++)
		// 	{
		// 		const auto driver = SDL_GetRenderDriver(i);
		// 		const auto checked = settings->renderer != nullptr && SDL_strcmp(driver,
		// 			settings->renderer) == 0;
		//
		// 		if (nk_button_symbol_label(state->ctx, radio_symbol(checked), driver,
		// 			NK_TEXT_ALIGN_LEFT))
		// 		{
		// 			settings->renderer = driver;
		// 		}
		// 	}
		//
		// 	nk_group_end(state->ctx);
		// }

		// if (nk_group_begin(state->ctx, "", 0))
		// {
		// 	nk_layout_row_dynamic(state->ctx, item_height, 1);
		//
		// 	if (nk_button_symbol_label(state->ctx, radio_symbol(settings->audio_driver == nullptr),
		// 		"auto", NK_TEXT_ALIGN_LEFT))
		// 	{
		// 		settings->audio_driver = nullptr;
		// 	}
		//
		// 	const auto num = SDL_GetNumAudioDrivers();
		// 	for (auto i = 0; i < num; i++)
		// 	{
		// 		const auto driver = SDL_GetAudioDriver(i);
		// 		const auto checked = settings->audio_driver != nullptr && SDL_strcmp(driver,
		// 			settings->audio_driver) == 0;
		//
		// 		if (nk_button_symbol_label(state->ctx, radio_symbol(checked), driver,
		// 			NK_TEXT_ALIGN_LEFT))
		// 		{
		// 			settings->audio_driver = driver;
		// 		}
		// 	}
		//
		// 	nk_group_end(state->ctx);
		// }

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
