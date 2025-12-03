#include "caw/gui/menubar.h"
#include "caw/appstate.h"
#include "caw/guistate.h"
#include "caw/gui/apptheme.h"
#include "caw/res/icons.h"

#include "shiny/menubar.h"
#include "shiny/image.h"
#include "shiny/init.h"
#include "shiny/label.h"
#include "shiny/menubaritem.h"
#include "shiny/menucontent.h"
#include "shiny/menuitem.h"
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

static void SDLCALL on_file_opened(void *userdata, const char *const *filelist, int filter)
{
}

void menu_item(app_state_t *state, const menu_item_config_t *item)
{
	Clay_Context *context = shiny_state_clay_context(state->shiny);

	shiny_menu_item_begin(context, item->element_id);
	{
		if (item->icon != nullptr)
		{
			SDL_Texture *texture = icon(state->renderer, item->icon);
			const shiny_size_t size = {
				.width = 24,
				.height = 24,
			};
			shiny_image(context, texture, &size);
		}

		shiny_label(context, item->text, FONT_SIZE_MENU);
	}
	if (shiny_menu_item_end())
	{
		if (item->clicked != nullptr)
		{
			item->clicked(state);
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

static void menubar_item(app_state_t *state, const char *element_id,
	const char *text, const menu_item_config_t *items, const size_t count)
{
	Clay_Context *context = shiny_state_clay_context(state->shiny);

	const bool open = shiny_menubar_item_begin(context, element_id);
	{
		shiny_label(context, text, FONT_SIZE_MENU);

		if (open)
		{
			shiny_menu_content_begin(context);
			{
				menu_items(state, items, count);
			}
			shiny_menu_content_end();
		}
	}
	shiny_menubar_item_end();
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
	menubar_item(state, "FileMenuItem", "File",
		(menu_item_config_t[]){
			{
				.element_id = "New",
				.text = "New...",
			},
			{
				.element_id = "Open",
				.text = "Open...",
				.clicked = on_file_open_clicked,
			},
			{
				.element_id = "Save",
				.text = "Save",
			},
			{
				.element_id = "SaveAs",
				.text = "Save As...",
			},
			{
				.element_id = "Export",
				.text = "Export...",
			},
			{
				.element_id = "Quit",
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
	menubar_item(state, "ViewMenuItem", "View",
		(menu_item_config_t[]){
			{
				.element_id = "Settings",
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
	menubar_item(state, "DebugMenuItem", "Debug",
		(menu_item_config_t[]){
		}, 0
	);
}

void help_menu(app_state_t *state)
{
	menubar_item(state, "HelpMenuItem", "Help",
		(menu_item_config_t[]){
			{
				.element_id = "About",
				.text = "About...",
			},
		}, 1
	);
}

void fps_counter(app_state_t *state)
{
	SDL_snprintf(state->gui.timer.text, 8, "%.0f FPS", state->gui.timer.fps);
	Clay_Context *context = shiny_state_clay_context(state->shiny);
	shiny_label(context, state->gui.timer.text, FONT_SIZE_MENU);
}

void menubar(app_state_t *state)
{
	Clay_Context *context = shiny_state_clay_context(state->shiny);
	shiny_menubar_begin(context, "Menubar");
	{
		file_menu(state);
		view_menu(state);
		debug_menu(state);
		help_menu(state);

		shiny_h_spacer(context);

		fps_counter(state);
	}
	shiny_menubar_end();
}
