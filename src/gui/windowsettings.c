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
#include "shiny/spacer.h"
#include "shiny/themekey.h"
#include "shiny/window.h"
#include "shiny/internal/color.h"

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

Clay_TextElementConfig body_text_config()
{
	return (Clay_TextElementConfig){
		.fontSize = FONT_SIZE_BODY,
		.textColor = shiny_clay_theme_color(SHINY_COLOR_FOREGROUND),
	};
}

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

	const Clay_ElementDeclaration content = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.childAlignment = (Clay_ChildAlignment){
				.y = CLAY_ALIGN_Y_CENTER,
			},
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
		},
	};

	CLAY_AUTO_ID(content)
	{
		CLAY_TEXT(CLAY_STRING("Renderer"), CLAY_TEXT_CONFIG(body_text_config()));
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
	CLAY_AUTO_ID(content)
	{
		CLAY_TEXT(CLAY_STRING("Audio driver"), CLAY_TEXT_CONFIG(body_text_config()));
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
