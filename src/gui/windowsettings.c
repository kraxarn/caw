#include "caw/gui/windowsettings.h"
#include "caw/appstate.h"
#include "caw/audiodriver.h"
#include "caw/guistate.h"
#include "caw/renderdriver.h"
#include "caw/settings.h"
#include "caw/gui/apptheme.h"

#include "shiny/combobox.h"
#include "shiny/comboboxoption.h"
#include "shiny/label.h"
#include "shiny/layout.h"
#include "shiny/spacer.h"
#include "shiny/window.h"

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

void set_render_driver(app_state_t *state, const char *value)
{
	state->gui.settings.render_driver = value;

	settings_set_string(state->settings, "render_driver",
		state->gui.settings.render_driver
	);
	settings_flush(state->settings);
}

void set_audio_driver(app_state_t *state, const char *value)
{
	state->gui.settings.audio_driver = value;

	settings_set_string(state->settings, "audio_driver",
		state->gui.settings.audio_driver
	);
	settings_flush(state->settings);
}

static void render_driver(app_state_t *state, const shiny_layout_flag_t flags)
{
	shiny_layout_begin(nullptr, flags);
	{
		shiny_label("Render driver", FONT_SIZE_BODY);
		shiny_h_spacer();

		const char *current = state->gui.settings.render_driver == nullptr
			? "Auto"
			: render_driver_display_name(state->gui.settings.render_driver);

		if (shiny_combobox_begin("RenderDriver", current, FONT_SIZE_BODY, SDL_GetNumRenderDrivers() + 1))
		{
			if (shiny_combobox_option("auto", "Auto", FONT_SIZE_BODY))
			{
				set_render_driver(state, nullptr);
			}

			for (auto i = 0; i < SDL_GetNumRenderDrivers(); i++)
			{
				const char *name = SDL_GetRenderDriver(i);
				const char *display_name = render_driver_display_name(name);

				if (shiny_combobox_option(name, display_name, FONT_SIZE_BODY))
				{
					set_render_driver(state, name);
				}
			}
		}
		shiny_combobox_end();
	}
	shiny_layout_end();
}

static void audio_driver(app_state_t *state, const shiny_layout_flag_t flags)
{
	shiny_layout_begin(nullptr, flags);
	{
		shiny_label("Audio driver", FONT_SIZE_BODY);
		shiny_h_spacer();

		const char *current_audio_driver = state->gui.settings.audio_driver == nullptr
			? "Auto"
			: audio_driver_display_name(state->gui.settings.audio_driver);

		if (shiny_combobox_begin("AudioDriver", current_audio_driver, FONT_SIZE_BODY, SDL_GetNumAudioDrivers() + 1))
		{
			if (shiny_combobox_option("auto", "Auto", FONT_SIZE_BODY))
			{
				set_audio_driver(state, nullptr);
			}

			for (auto i = 0; i < SDL_GetNumAudioDrivers(); i++)
			{
				const char *name = SDL_GetAudioDriver(i);
				const char *display_name = audio_driver_display_name(name);

				if (shiny_combobox_option(name, display_name, FONT_SIZE_BODY))
				{
					set_audio_driver(state, name);
				}
			}
		}
		shiny_combobox_end();
	}
	shiny_layout_end();
}

void settings_window(app_state_t *state)
{
	constexpr auto width = 340.F;
	constexpr auto height = 300.F;
	const SDL_FRect size = {
		.w = width,
		.h = height,
	};

	shiny_window_begin("SettingsWindow", size, "Settings", FONT_SIZE_TITLE);
	{
		constexpr shiny_layout_flag_t flags =
			SHINY_LAYOUT_LEFT_TO_RIGHT
			| SHINY_ALIGN_Y_CENTER
			| SHINY_SIZE_GROW_X;

		render_driver(state, flags);
		audio_driver(state, flags);
	}
	shiny_window_end();
}
