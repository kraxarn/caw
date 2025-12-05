#include "caw/gui/windowsettings.h"
#include "caw/appstate.h"
#include "caw/audiodriver.h"
#include "caw/guistate.h"
#include "caw/renderdriver.h"
#include "caw/settings.h"
#include "caw/gui/apptheme.h"

#include "shiny/combobox.h"
#include "shiny/comboboxoption.h"
#include "shiny/init.h"
#include "shiny/label.h"
#include "shiny/layout.h"
#include "shiny/spacer.h"
#include "shiny/window.h"

#include "clay.h"

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

typedef const char *(*cb_item_callback_t)(int index);

typedef struct cb_settings_t
{
	const char *value;
	cb_item_callback_t items;
	int size;
	cb_select_callback_t callback;
} cb_settings_t;

const char *render_driver(const int index)
{
	if (index == 0)
	{
		return "Auto";
	}

	const char *name = SDL_GetRenderDriver(index - 1);
	return render_driver_display_name(name);
}

const char *audio_driver(const int index)
{
	if (index == 0)
	{
		return "Auto";
	}

	const char *name = SDL_GetAudioDriver(index - 1);
	return audio_driver_display_name(name);
}

void set_render_driver(app_state_t *state, const int index)
{
	state->gui.settings.renderer = index == 0
		? nullptr
		: SDL_GetRenderDriver(index - 1);

	settings_set_string(state->settings, "render_driver",
		state->gui.settings.renderer
	);
	settings_flush(state->settings);
}

void set_audio_driver(app_state_t *state, const int index)
{
	state->gui.settings.audio_driver = index == 0
		? nullptr
		: SDL_GetAudioDriver(index - 1);

	settings_set_string(state->settings, "audio_driver",
		state->gui.settings.audio_driver
	);
	settings_flush(state->settings);
}

void combobox(app_state_t *state, const char *element_id, const cb_settings_t settings)
{
	Clay_Context *context = shiny_state_clay_context(state->shiny);

	if (shiny_combobox_begin(context, element_id, settings.value, FONT_SIZE_BODY, settings.size))
	{
		for (auto i = 0; i < settings.size; i++)
		{
			const char *item = settings.items(i);
			if (shiny_combobox_option(context, item, item, FONT_SIZE_BODY))
			{
				settings.callback(state, i);
			}
		}
	}
	shiny_combobox_end();
}

void window_content(app_state_t *state)
{
	Clay_Context *context = shiny_state_clay_context(state->shiny);

	constexpr shiny_layout_flag_t flags =
		SHINY_LAYOUT_LEFT_TO_RIGHT
		| SHINY_ALIGN_Y_CENTER
		| SHINY_SIZE_GROW_X;

	shiny_layout_begin(context, nullptr, flags);
	{
		shiny_label(context, "Renderer", FONT_SIZE_BODY);
		shiny_h_spacer(context);
		combobox(state, "Renderer", (cb_settings_t){
			.value = state->gui.settings.renderer == nullptr
				? render_driver(0)
				: render_driver_display_name(state->gui.settings.renderer),
			.items = render_driver,
			.size = SDL_GetNumRenderDrivers() + 1,
			.callback = set_render_driver,
		});
	}
	shiny_layout_end();

	shiny_layout_begin(context, nullptr, flags);
	{
		shiny_label(context, "Auto driver", FONT_SIZE_BODY);
		shiny_h_spacer(context);
		combobox(state, "AudioDriver", (cb_settings_t){
			.value = state->gui.settings.audio_driver == nullptr
				? render_driver(0)
				: audio_driver_display_name(state->gui.settings.audio_driver),
			.items = audio_driver,
			.size = SDL_GetNumAudioDrivers() + 1,
			.callback = set_audio_driver,
		});
	}
	shiny_layout_end();
}

void settings_window(app_state_t *state)
{
	Clay_Context *context = shiny_state_clay_context(state->shiny);

	constexpr auto width = 340.F;
	constexpr auto height = 300.F;
	const SDL_FRect size = {
		.w = width,
		.h = height,
	};

	shiny_window_begin(context, "SettingsWindow", size, "Settings", FONT_SIZE_TITLE);
	{
		window_content(state);
	}
	shiny_window_end();
}
