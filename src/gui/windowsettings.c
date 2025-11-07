#include "caw/gui/windowsettings.h"
#include "caw/ui.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_audio.h>

void draw_combo_renderer(app_state_t *state)
{
	nk_label(state->ctx, "Renderer", NK_TEXT_LEFT);

	gui_settings_state_t *settings = &state->gui.settings;

	const auto renderer = settings->renderer != nullptr
		? settings->renderer
		: "auto";

	if (nk_combo_begin_label(state->ctx, renderer, nk_vec2(150, 300)))
	{
		nk_layout_row_dynamic(state->ctx, 30, 1);

		if (nk_combo_item_label(state->ctx, "auto",
			NK_TEXT_ALIGN_LEFT))
		{
			settings->renderer = "auto";
		}

		const auto num = SDL_GetNumRenderDrivers();
		for (auto i = 0; i < num; i++)
		{
			const auto driver = SDL_GetRenderDriver(i);
			if (nk_combo_item_label(state->ctx, driver,
				NK_TEXT_ALIGN_LEFT))
			{
				settings->renderer = driver;
			}
		}

		nk_combo_end(state->ctx);
	}
}

void draw_combo_audio_driver(app_state_t *state)
{
	nk_label(state->ctx, "Audio driver", NK_TEXT_LEFT);

	gui_settings_state_t *settings = &state->gui.settings;

	const auto audio_driver = settings->audio_driver != nullptr
		? settings->audio_driver
		: "auto";

	if (nk_combo_begin_label(state->ctx, audio_driver, nk_vec2(150, 300)))
	{
		nk_layout_row_dynamic(state->ctx, 30, 1);

		if (nk_combo_item_label(state->ctx, "auto", NK_TEXT_ALIGN_LEFT))
		{
			settings->audio_driver = "auto";
		}

		const auto num = SDL_GetNumAudioDrivers();
		for (auto i = 0; i < num; i++)
		{
			const auto driver = SDL_GetAudioDriver(i);
			if (nk_combo_item_label(state->ctx, driver, NK_TEXT_ALIGN_LEFT))
			{
				settings->audio_driver = driver;
			}
		}

		nk_combo_end(state->ctx);
	}
}

void draw_settings_window(app_state_t *state)
{
	if (nk_begin(state->ctx, "Settings", nk_rect(50, 50, 220, 220),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_SCALABLE))
	{
		nk_layout_row_dynamic(state->ctx, 30, 2);

		draw_combo_renderer(state);
		draw_combo_audio_driver(state);

		nk_end(state->ctx);
	}
}
