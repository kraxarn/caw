#include "caw/gui/windowsettings.h"
#include "caw/appstate.h"
#include "caw/gui/apptheme.h"

#include "clay.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_audio.h>

typedef const char *(*cb_item_callback)(int index);

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

void combobox_option(Clay_String text)
{
	const Clay_ElementDeclaration wrapper = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.padding = CLAY_PADDING_ALL(PADDING_COMBOBOX/2),
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
		},
	};

	Clay_ElementDeclaration content = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.padding = CLAY_PADDING_ALL(PADDING_COMBOBOX/2),
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
		},
		.cornerRadius = CLAY_CORNER_RADIUS(CORNER_RADIUS_CONTROL),
	};

	CLAY_AUTO_ID(wrapper)
	{
		content.backgroundColor = app_color_clay(
			(int) Clay_Hovered()
			? COLOR_CONTROL_ACTIVE
			: COLOR_CONTROL_BACKGROUND
		);

		CLAY_AUTO_ID(content)
		{
			CLAY_TEXT(text, CLAY_TEXT_CONFIG(body_text_config()));
		}
	}
}

void combobox_options(const cb_item_callback items, const int size)
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
				.width = CLAY_SIZING_FIXED(WIDTH_COMBOBOX),
				.height = CLAY_SIZING_GROW(HEIGHT_COMBOBOX * size),
			},
		},
		.backgroundColor = app_color_clay(COLOR_CONTROL_BACKGROUND),
		.cornerRadius = (Clay_CornerRadius){
			.bottomLeft = CORNER_RADIUS_CONTROL,
			.bottomRight = CORNER_RADIUS_CONTROL,
		},
	};

	CLAY_AUTO_ID(element)
	{
		for (auto i = 0; i < size; i++)
		{
			const char *item = items(i);
			combobox_option((Clay_String){
				.isStaticallyAllocated = true,
				.length = SDL_strlen(item),
				.chars = item,
			});
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

void combobox(app_state_t *state, Clay_String id, const cb_item_callback items, const int size)
{
	const int is_open = state->gui.windows.current_combobox.id == Clay_GetElementId(id).id;

	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_FIXED(WIDTH_COMBOBOX),
				.height = CLAY_SIZING_GROW(0),
			},
			.padding = CLAY_PADDING_ALL(PADDING_CONTROL),
		},
		.backgroundColor = app_color_clay(COLOR_CONTROL_BACKGROUND),
		.cornerRadius = (Clay_CornerRadius){
			.topLeft = CORNER_RADIUS_CONTROL,
			.topRight = CORNER_RADIUS_CONTROL,
			.bottomLeft = is_open ? 0 : CORNER_RADIUS_CONTROL,
			.bottomRight = is_open ? 0 : CORNER_RADIUS_CONTROL,
		},
	};

	CLAY(CLAY_SID(id), element)
	{
		CLAY_TEXT(CLAY_STRING("auto"), CLAY_TEXT_CONFIG(body_text_config()));
		spacer_x();
		CLAY_TEXT(is_open ? CLAY_STRING("^") : CLAY_STRING("V"), CLAY_TEXT_CONFIG(body_text_config()));

		Clay_OnHover(on_combobox_hover, (intptr_t) state);

		if (is_open)
		{
			combobox_options(items, size);
		}
	}
}

void window_content(app_state_t *state)
{
	const Clay_ElementDeclaration wrapper = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.childGap = GAP_WINDOW_ITEM,
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
			combobox(state, CLAY_STRING("Renderer"), render_driver, SDL_GetNumRenderDrivers() + 1);
		}
		CLAY_AUTO_ID(content)
		{
			CLAY_TEXT(CLAY_STRING("Audio driver"), CLAY_TEXT_CONFIG(body_text_config()));
			spacer_x();
			combobox(state, CLAY_STRING("AudioDriver"), audio_driver, SDL_GetNumAudioDrivers() + 1);
		}
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
		window_content(state);
	}
}
