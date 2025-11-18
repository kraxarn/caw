#include "caw/gui/windowsettings.h"
#include "caw/appstate.h"
#include "caw/guistate.h"
#include "caw/gui/apptheme.h"

#include "shiny/theme.h"
#include "shiny/themekey.h"
#include "shiny/internal/color.h"

#include "clay.h"

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_render.h>

typedef const char *(*cb_item_callback_t)(int index);

typedef struct cb_settings_t
{
	const char *value;
	cb_item_callback_t items;
	int size;
	cb_select_callback_t callback;
} cb_settings_t;

Clay_TextElementConfig title_text_config()
{
	return (Clay_TextElementConfig){
		.fontSize = FONT_SIZE_TITLE,
		.textColor = shiny_clay_theme_color(SHINY_COLOR_FOREGROUND),
	};
}

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
		return "auto";
	}

	return SDL_GetRenderDriver(index - 1);
}

const char *audio_driver(const int index)
{
	if (index == 0)
	{
		return "auto";
	}

	return SDL_GetAudioDriver(index - 1);
}

void set_render_driver(app_state_t *state, const int index)
{
	state->gui.settings.renderer = index == 0
		? nullptr
		: SDL_GetRenderDriver(index - 1);
}

void set_audio_driver(app_state_t *state, const int index)
{
	state->gui.settings.audio_driver = index == 0
		? nullptr
		: SDL_GetAudioDriver(index - 1);
}

void on_window_title_hover(const Clay_ElementId element_id,
	const Clay_PointerData pointer_data, const intptr_t user_data)
{
	const auto state = (gui_window_state_t *) user_data;

	if (pointer_data.state == CLAY_POINTER_DATA_PRESSED)
	{
		if (state->offset.x == 0 || state->offset.y == 0)
		{
			const auto data = Clay_GetElementData(element_id);
			state->offset.x = pointer_data.position.x - data.boundingBox.x;
			state->offset.y = pointer_data.position.y - data.boundingBox.y;
			state->attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
		}

		state->position.x = pointer_data.position.x - (state->offset.x);
		state->position.y = pointer_data.position.y - (state->offset.y);
	}

	if (pointer_data.state == CLAY_POINTER_DATA_RELEASED_THIS_FRAME)
	{
		state->offset = (Clay_Vector2){};
	}
}

void window_title(const app_state_t *state, const Clay_String text)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
			.padding = (Clay_Padding){
				.left = shiny_theme_padding(SHINY_PADDING_WINDOW_HEADER_X),
				.right = shiny_theme_padding(SHINY_PADDING_WINDOW_HEADER_X),
				.top = shiny_theme_padding(SHINY_PADDING_WINDOW_HEADER_Y),
				.bottom = shiny_theme_padding(SHINY_PADDING_WINDOW_HEADER_Y),
			},
		},
		.backgroundColor = shiny_clay_theme_color(SHINY_COLOR_WINDOW_HEADER),
		.cornerRadius = (Clay_CornerRadius){
			.topLeft = shiny_theme_corner_radius(SHINY_CORNER_RADIUS_WINDOW),
			.topRight = shiny_theme_corner_radius(SHINY_CORNER_RADIUS_WINDOW),
		},
	};

	CLAY_AUTO_ID(element)
	{
		Clay_OnHover(on_window_title_hover, (intptr_t) &state->gui.windows.settings);

		CLAY_TEXT(text, CLAY_TEXT_CONFIG(title_text_config()));
	}
}

void spacer_x()
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
		},
	};

	CLAY_AUTO_ID(element)
	{
	}
}

void on_combobox_option_hover([[maybe_unused]] Clay_ElementId element_id,
	Clay_PointerData pointer_data, intptr_t user_data)
{
	if (pointer_data.state != CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
	{
		return;
	}

	const auto state = (app_state_t *) user_data;
	const auto data = &state->gui.windows.current_combobox_item;
	data->callback(state, data->index);
	state->gui.windows.current_combobox = (Clay_ElementId){};
}

void combobox_option(app_state_t *state, const int index,
	const Clay_String text, const cb_select_callback_t callback)
{
	const Clay_ElementDeclaration wrapper = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.padding = CLAY_PADDING_ALL(shiny_theme_padding(SHINY_PADDING_COMBOBOX)/2),
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
		},
	};

	Clay_ElementDeclaration content = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.padding = CLAY_PADDING_ALL(shiny_theme_padding(SHINY_PADDING_COMBOBOX)/2),
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
		},
		.cornerRadius = CLAY_CORNER_RADIUS(shiny_theme_corner_radius(SHINY_CORNER_RADIUS_CONTROL)),
	};

	CLAY_AUTO_ID(wrapper)
	{
		content.backgroundColor = shiny_clay_theme_color(
			(int) Clay_Hovered()
				? SHINY_COLOR_CONTROL_ACTIVE
				: SHINY_COLOR_CONTROL_BACKGROUND
		);

		if (Clay_Hovered())
		{
			state->gui.windows.current_combobox_item.index = index;
			state->gui.windows.current_combobox_item.callback = callback;
			Clay_OnHover(on_combobox_option_hover, (intptr_t) state);
		}

		CLAY_AUTO_ID(content)
		{
			CLAY_TEXT(text, CLAY_TEXT_CONFIG(body_text_config()));
		}
	}
}

void combobox_options(app_state_t *state, const cb_settings_t settings)
{
	const Clay_ElementDeclaration element = {
		.floating = (Clay_FloatingElementConfig){
			.attachTo = CLAY_ATTACH_TO_PARENT,
			.attachPoints = (Clay_FloatingAttachPoints){
				.parent = CLAY_ATTACH_POINT_LEFT_BOTTOM,
			},
		},
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_FIXED(shiny_theme_size(SHINY_WIDTH_COMBOBOX)),
				.height = CLAY_SIZING_GROW(shiny_theme_size(SHINY_HEIGHT_COMBOBOX) * settings.size),
			},
		},
		.backgroundColor = shiny_clay_theme_color(SHINY_COLOR_CONTROL_BACKGROUND),
		.cornerRadius = (Clay_CornerRadius){
			.bottomLeft = shiny_theme_corner_radius(SHINY_CORNER_RADIUS_CONTROL),
			.bottomRight = shiny_theme_corner_radius(SHINY_CORNER_RADIUS_CONTROL),
		},
	};

	CLAY_AUTO_ID(element)
	{
		for (auto i = 0; i < settings.size; i++)
		{
			const char *item = settings.items(i);
			const Clay_String text = {
				.isStaticallyAllocated = true,
				.length = SDL_strlen(item),
				.chars = item,
			};
			combobox_option(state, i, text, settings.callback);
		}
	}
}

void on_combobox_hover(Clay_ElementId element_id,
	Clay_PointerData pointer_data, intptr_t user_data)
{
	if (pointer_data.state != CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
	{
		return;
	}

	const auto state = (app_state_t *) user_data;

	if (state->gui.windows.current_combobox.id == 0
		|| state->gui.windows.current_combobox.id != element_id.id)
	{
		state->gui.windows.current_combobox = element_id;
	}
	else
	{
		state->gui.windows.current_combobox = (Clay_ElementId){};
	}
}

void combobox(app_state_t *state, Clay_String id, const cb_settings_t settings)
{
	const int is_open = state->gui.windows.current_combobox.id == Clay_GetElementId(id).id;

	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_FIXED(shiny_theme_size(SHINY_WIDTH_COMBOBOX)),
				.height = CLAY_SIZING_GROW(0),
			},
			.padding = CLAY_PADDING_ALL(shiny_theme_padding(SHINY_PADDING_CONTROL)),
		},
		.backgroundColor = shiny_clay_theme_color(SHINY_COLOR_CONTROL_BACKGROUND),
		.cornerRadius = (Clay_CornerRadius){
			.topLeft = shiny_theme_corner_radius(SHINY_CORNER_RADIUS_CONTROL),
			.topRight = shiny_theme_corner_radius(SHINY_CORNER_RADIUS_CONTROL),
			.bottomLeft = is_open ? 0 : shiny_theme_corner_radius(SHINY_CORNER_RADIUS_CONTROL),
			.bottomRight = is_open ? 0 : shiny_theme_corner_radius(SHINY_CORNER_RADIUS_CONTROL),
		},
	};

	CLAY(CLAY_SID(id), element)
	{
		const Clay_String value = {
			.isStaticallyAllocated = false,
			.length = SDL_strlen(settings.value),
			.chars = settings.value,
		};

		CLAY_TEXT(value, CLAY_TEXT_CONFIG(body_text_config()));
		spacer_x();
		CLAY_TEXT(is_open ? CLAY_STRING("^") : CLAY_STRING("V"), CLAY_TEXT_CONFIG(body_text_config()));

		Clay_OnHover(on_combobox_hover, (intptr_t) state);

		if (is_open)
		{
			combobox_options(state, settings);
		}
	}
}

void window_content(app_state_t *state)
{
	const Clay_ElementDeclaration wrapper = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.childGap = shiny_theme_gap(SHINY_GAP_WINDOW_ITEM),
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
				.height = CLAY_SIZING_GROW(0),
			},
			.padding = CLAY_PADDING_ALL(shiny_theme_padding(SHINY_PADDING_WINDOW_CONTENT)),
		},
		.backgroundColor = shiny_clay_theme_color(SHINY_COLOR_WINDOW_BACKGROUND),
		.cornerRadius = (Clay_CornerRadius){
			.bottomLeft = shiny_theme_corner_radius(SHINY_CORNER_RADIUS_WINDOW),
			.bottomRight = shiny_theme_corner_radius(SHINY_CORNER_RADIUS_WINDOW),
		},
	};

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

	CLAY_AUTO_ID(wrapper)
	{
		CLAY_AUTO_ID(content)
		{
			CLAY_TEXT(CLAY_STRING("Renderer"), CLAY_TEXT_CONFIG(body_text_config()));
			spacer_x();
			combobox(state, CLAY_STRING("Renderer"), (cb_settings_t){
				.value = state->gui.settings.renderer == nullptr
					? "auto"
					: state->gui.settings.renderer,
				.items = render_driver,
				.size = SDL_GetNumRenderDrivers() + 1,
				.callback = set_render_driver,
			});
		}
		CLAY_AUTO_ID(content)
		{
			CLAY_TEXT(CLAY_STRING("Audio driver"), CLAY_TEXT_CONFIG(body_text_config()));
			spacer_x();
			combobox(state, CLAY_STRING("AudioDriver"), (cb_settings_t){
				.value = state->gui.settings.audio_driver == nullptr
					? "auto"
					: state->gui.settings.audio_driver,
				.items = audio_driver,
				.size = SDL_GetNumAudioDrivers() + 1,
				.callback = set_audio_driver,
			});
		}
	}
}

void settings_window(app_state_t *state)
{
	constexpr auto width = 350.F;
	constexpr auto height = 300.F;

	const auto window = &state->gui.windows.settings;
	if (window->position.x == 0 || window->position.y == 0)
	{
		window->position.x = -width / 2;
		window->position.y = -height / 2;
		window->attach_point = CLAY_ATTACH_POINT_CENTER_CENTER;
	}

	const Clay_ElementDeclaration element = {
		.floating = (Clay_FloatingElementConfig){
			.attachTo = CLAY_ATTACH_TO_ROOT,
			.attachPoints = (Clay_FloatingAttachPoints){
				.parent = window->attach_point,
			},
			.offset = window->position,
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
		window_title(state, CLAY_STRING("Settings"));
		window_content(state);
	}
}
