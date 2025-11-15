#include "caw/gui/windowsettings.h"
#include "caw/appstate.h"
#include "caw/gui/apptheme.h"

#include "clay.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_audio.h>

Clay_TextElementConfig title_text_config()
{
	return (Clay_TextElementConfig){
		.fontSize = FONT_SIZE_TITLE,
		.textColor = app_color_clay(COLOR_FOREGROUND),
	};
}

Clay_TextElementConfig body_text_config()
{
	return (Clay_TextElementConfig){
		.fontSize = FONT_SIZE_BODY,
		.textColor = app_color_clay(COLOR_FOREGROUND),
	};
}

// void draw_combo_renderer(app_state_t *state)
// {
// 	nk_label(state->ctx, "Renderer", NK_TEXT_LEFT);
//
// 	gui_settings_state_t *settings = &state->gui.settings;
//
// 	const auto renderer = settings->renderer != nullptr
// 		? settings->renderer
// 		: "auto";
//
// 	if (nk_combo_begin_label(state->ctx, renderer, nk_vec2(150, 300)))
// 	{
// 		nk_layout_row_dynamic(state->ctx, 30, 1);
//
// 		if (nk_combo_item_label(state->ctx, "auto",
// 			NK_TEXT_ALIGN_LEFT))
// 		{
// 			settings->renderer = "auto";
// 		}
//
// 		const auto num = SDL_GetNumRenderDrivers();
// 		for (auto i = 0; i < num; i++)
// 		{
// 			const auto driver = SDL_GetRenderDriver(i);
// 			if (nk_combo_item_label(state->ctx, driver,
// 				NK_TEXT_ALIGN_LEFT))
// 			{
// 				settings->renderer = driver;
// 			}
// 		}
//
// 		nk_combo_end(state->ctx);
// 	}
// }

// void draw_combo_audio_driver(app_state_t *state)
// {
// 	nk_label(state->ctx, "Audio driver", NK_TEXT_LEFT);
//
// 	gui_settings_state_t *settings = &state->gui.settings;
//
// 	const auto audio_driver = settings->audio_driver != nullptr
// 		? settings->audio_driver
// 		: "auto";
//
// 	if (nk_combo_begin_label(state->ctx, audio_driver, nk_vec2(150, 300)))
// 	{
// 		nk_layout_row_dynamic(state->ctx, 30, 1);
//
// 		if (nk_combo_item_label(state->ctx, "auto", NK_TEXT_ALIGN_LEFT))
// 		{
// 			settings->audio_driver = "auto";
// 		}
//
// 		const auto num = SDL_GetNumAudioDrivers();
// 		for (auto i = 0; i < num; i++)
// 		{
// 			const auto driver = SDL_GetAudioDriver(i);
// 			if (nk_combo_item_label(state->ctx, driver, NK_TEXT_ALIGN_LEFT))
// 			{
// 				settings->audio_driver = driver;
// 			}
// 		}
//
// 		nk_combo_end(state->ctx);
// 	}
// }

void window_title(Clay_String text)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
			.padding = (Clay_Padding){
				.left = PADDING_WINDOW_HEADER_X,
				.right = PADDING_WINDOW_HEADER_X,
				.top = PADDING_WINDOW_HEADER_Y,
				.bottom = PADDING_WINDOW_HEADER_Y,
			},
		},
		.backgroundColor = app_color_clay(COLOR_WINDOW_HEADER),
		.cornerRadius = (Clay_CornerRadius){
			.topLeft = CORNER_RADIUS_WINDOW,
			.topRight = CORNER_RADIUS_WINDOW,
		},
	};

	CLAY_AUTO_ID(element)
	{
		CLAY_TEXT(text, CLAY_TEXT_CONFIG(title_text_config()));
	}
}

void window_content()
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
				.height = CLAY_SIZING_GROW(0),
			},
			.padding = CLAY_PADDING_ALL(PADDING_WINDOW_CONTENT),
		},
		.backgroundColor = app_color_clay(COLOR_WINDOW_BACKGROUND),
		.cornerRadius = (Clay_CornerRadius){
			.bottomLeft = CORNER_RADIUS_WINDOW,
			.bottomRight = CORNER_RADIUS_WINDOW,
		},
	};

	CLAY_AUTO_ID(element)
	{
		CLAY_TEXT(CLAY_STRING("Renderer"), CLAY_TEXT_CONFIG(body_text_config()));
		CLAY_TEXT(CLAY_STRING("Audio driver"), CLAY_TEXT_CONFIG(body_text_config()));
	}
}

void settings_window(app_state_t *state)
{
	constexpr auto width = 350.F;
	constexpr auto height = 300.F;

	const Clay_ElementDeclaration element = {
		.floating = (Clay_FloatingElementConfig){
			.attachTo = CLAY_ATTACH_TO_ROOT,
			.attachPoints = (Clay_FloatingAttachPoints){
				.parent = CLAY_ATTACH_POINT_CENTER_CENTER,
			},
			.offset = (Clay_Vector2){
				.x = -width / 2.F,
				.y = -height / 2.F,
			}
		},
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_FIXED(width),
				.height = CLAY_SIZING_FIXED(height),
			},
		},
	};

	CLAY(CLAY_ID("SettingsWindow"), element)
	{
		window_title(CLAY_STRING("Settings"));
		window_content();
	}
}
