#include "caw/gui/menubar.h"
#include "caw/appstate.h"
#include "caw/guistate.h"
#include "caw/gui/apptheme.h"
#include "caw/res/icons.h"

#include "shiny/menubar.h"
#include "shiny/image.h"
#include "shiny/label.h"
#include "shiny/size.h"
#include "shiny/spacer.h"
#include "shiny/theme.h"
#include "shiny/themekey.h"
#include "shiny/internal/color.h"

#include "clay.h"

#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

void SDLCALL on_file_opened(void *userdata, const char *const *filelist, int filter)
{
}

Clay_TextElementConfig text_config()
{
	return (Clay_TextElementConfig){
		.fontSize = FONT_SIZE_MENU,
		.textColor = shiny_clay_theme_color(SHINY_COLOR_FOREGROUND),
	};
}

void on_menu_item_hover([[maybe_unused]] Clay_ElementId element_id,
	Clay_PointerData pointer_data, intptr_t user_data)
{
	if (pointer_data.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
	{
		const auto data = (menu_item_hover_data_t *) user_data;
		if (data->config.clicked != nullptr)
		{
			data->config.clicked(data->state);
			data->state->gui.menu.visible = false;
		}
	}
}

void menu_item(app_state_t *state, const menu_item_config_t *item)
{
	Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(0),
			},
		},
	};

	CLAY_AUTO_ID(element)
	{
		element.layout.padding = CLAY_PADDING_ALL(shiny_theme_padding(SHINY_PADDING_MENU_ITEM));
		element.cornerRadius = CLAY_CORNER_RADIUS(shiny_theme_corner_radius(SHINY_CORNER_RADIUS_DEFAULT));
		element.backgroundColor = shiny_clay_theme_color(
			(int) Clay_Hovered()
			? SHINY_COLOR_CONTROL_HOVER
			: SHINY_COLOR_CONTROL_ACTIVE
		);
		element.layout.childAlignment.y = CLAY_ALIGN_Y_CENTER;
		element.layout.childGap = shiny_theme_gap(SHINY_GAP_DEFAULT);

		if (Clay_Hovered())
		{
			state->gui.menu.current_item.config = *item;
			state->gui.menu.current_item.state = state;
			Clay_OnHover(on_menu_item_hover, (intptr_t) &state->gui.menu.current_item);
		}

		CLAY_AUTO_ID(element)
		{
			if (item->icon != nullptr)
			{
				SDL_Texture *texture = icon(state->renderer, item->icon);
				const shiny_size_t size = {
					.width = 24,
					.height = 24,
				};
				shiny_image(state->clay_context, texture, &size);
			}

			shiny_label(state->clay_context, item->text, FONT_SIZE_MENU);
		}
	}
}

void menu_items(app_state_t *state, const menu_item_config_t *items, const size_t count)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_FIXED(200),
			},
		},
		.cornerRadius = CLAY_CORNER_RADIUS(shiny_theme_corner_radius(SHINY_CORNER_RADIUS_DEFAULT)),
		.backgroundColor = shiny_clay_theme_color(SHINY_COLOR_WINDOW_BACKGROUND),
	};

	CLAY_AUTO_ID(element)
	{
		for (size_t i = 0; i < count; i++)
		{
			menu_item(state, items + i);
		}
	}
}

void menu_content(app_state_t *state, const menu_item_config_t *items, const size_t count)
{
	const Clay_ElementDeclaration element = {
		.floating = (Clay_FloatingElementConfig){
			.attachTo = CLAY_ATTACH_TO_PARENT,
			.attachPoints = (Clay_FloatingAttachPoints){
				.parent = CLAY_ATTACH_POINT_LEFT_BOTTOM,
			},
		},
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_FIXED(200),
			},
			.padding = (Clay_Padding){
				.top = shiny_theme_padding(SHINY_PADDING_MENUBAR) + shiny_theme_gap(SHINY_GAP_DEFAULT),
			},
		},
	};

	CLAY_AUTO_ID(element)
	{
		menu_items(state, items, count);
	}
}

void on_menubar_item_hover(Clay_ElementId element_id, Clay_PointerData pointer_data, intptr_t user_data)
{
	const auto state = (app_state_t *) user_data;
	state->gui.menu.current = element_id;

	if (pointer_data.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
	{
		state->gui.menu.visible = (bool) !state->gui.menu.visible;
	}
}

void menubar_item(app_state_t *state, const Clay_String item_id, const Clay_String text,
	const menu_item_config_t *items, const size_t count)
{
	CLAY(CLAY_SID(item_id))
	{
		CLAY_TEXT(text, CLAY_TEXT_CONFIG(text_config()));
		Clay_OnHover(on_menubar_item_hover, (intptr_t) state);

		if ((int) state->gui.menu.visible && state->gui.menu.current.id == Clay__HashString(item_id, 0).id)
		{
			menu_content(state, items, count);
		}
	}
}

void on_file_open_clicked(app_state_t *state)
{
	const SDL_DialogFileFilter filters[] = {
		{"caw project", "caw"},
	};

	SDL_ShowOpenFileDialog(on_file_opened, nullptr, state->window, filters,
		1, nullptr, false);
}

void on_file_quit_clicked(app_state_t *state)
{
	state->result = SDL_APP_SUCCESS;
}

void file_menu(app_state_t *state)
{
	menubar_item(state, CLAY_STRING("FileMenuItem"), CLAY_STRING("File"),
		(menu_item_config_t[]){
			{.text = "New...",},
			{
				.text = "Open...",
				.clicked = on_file_open_clicked,
			},
			{.text = "Save",},
			{.text = "Save As...",},
			{.text = "Export...",},
			{
				.text = "Quit",
				.clicked = on_file_quit_clicked,
			},
		}, 6
	);
}

void on_view_settings_clicked(app_state_t *state)
{
	state->gui.windows.settings.visible = (bool) !state->gui.windows.settings.visible;
}

void view_menu(app_state_t *state)
{
	menubar_item(state, CLAY_STRING("ViewMenuItem"), CLAY_STRING("View"),
		(menu_item_config_t[]){
			{
				.icon = (int) state->gui.windows.settings.visible
				? "checkbox-marked"
				: "checkbox-blank-outline",
				.text = "Settings",
				.clicked = on_view_settings_clicked,
			},
		}, 1
	);
}

void debug_menu(app_state_t *state)
{
	menubar_item(state, CLAY_STRING("DebugMenuItem"), CLAY_STRING("Debug"),
		(menu_item_config_t[]){
		}, 0
	);
}

void help_menu(app_state_t *state)
{
	menubar_item(state, CLAY_STRING("HelpMenuItem"), CLAY_STRING("Help"),
		(menu_item_config_t[]){
			{.text = "About...",},
		}, 1
	);
}

void fps_counter(app_state_t *state)
{
	SDL_snprintf(state->gui.timer.text, 8, "%.0f FPS", state->gui.timer.fps);
	shiny_label(state->clay_context, state->gui.timer.text, FONT_SIZE_MENU);
}

void menubar(app_state_t *state)
{
	shiny_menubar_begin(state->clay_context, "Menubar");
	{
		file_menu(state);
		view_menu(state);
		debug_menu(state);
		help_menu(state);

		shiny_h_spacer(state->clay_context);

		fps_counter(state);
	}
	shiny_menubar_end();
}
