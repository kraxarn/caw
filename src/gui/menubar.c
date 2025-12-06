#include "caw/gui/menubar.h"
#include "caw/appstate.h"
#include "caw/guistate.h"
#include "caw/gui/apptheme.h"
#include "caw/res/icons.h"

#include "shiny/menubar.h"
#include "shiny/image.h"
#include "shiny/label.h"
#include "shiny/menu.h"
#include "shiny/menuitem.h"
#include "shiny/size.h"
#include "shiny/spacer.h"

#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

static void SDLCALL on_file_opened(void *userdata, const char *const *filelist, int filter)
{
}

static void menu_item(app_state_t *state, const menu_item_config_t *item)
{
	if (item->icon != nullptr)
	{
		SDL_Texture *texture = icon(state->renderer, item->icon);
		const shiny_size_t size = {
			.width = 24,
			.height = 24,
		};
		if (shiny_menu_item_icon(item->element_id, item->text, FONT_SIZE_MENU, texture, &size))
		{
			item->clicked(state);
		}
		return;
	}

	if (shiny_menu_item(item->element_id, item->text, FONT_SIZE_MENU))
	{
		item->clicked(state);
	}
}

static void menubar_item(app_state_t *state, const char *element_id,
	const char *text, const menu_item_config_t *items, const size_t count)
{
	if (shiny_menu_begin(element_id, text, FONT_SIZE_MENU))
	{
		for (size_t i = 0; i < count; i++)
		{
			menu_item(state, items + i);
		}
	}
	shiny_menu_end();
}

static void file_menu(app_state_t *state)
{
	if (shiny_menu_begin("FileMenu", "File", FONT_SIZE_MENU))
	{
		if (shiny_menu_item("FileNew", "New", FONT_SIZE_MENU))
		{
		}

		if (shiny_menu_item("FileOpen", "Open...", FONT_SIZE_MENU))
		{
			const SDL_DialogFileFilter filters[] = {
				{"caw project", "caw"},
			};

			SDL_ShowOpenFileDialog(on_file_opened, nullptr, state->window, filters,
				1, nullptr, false);
		}

		if (shiny_menu_item("FileSave", "Save", FONT_SIZE_MENU))
		{
		}

		if (shiny_menu_item("FileSaveAs", "Save As...", FONT_SIZE_MENU))
		{
		}

		if (shiny_menu_item("FileExport", "Export...", FONT_SIZE_MENU))
		{
		}

		if (shiny_menu_item("FileQuit", "Quit", FONT_SIZE_MENU))
		{
			state->result = SDL_APP_SUCCESS;
		}
	}
	shiny_menu_end();
}

static void on_view_settings_clicked(app_state_t *state)
{
	state->gui.windows.settings = (bool) !state->gui.windows.settings;
}

static void view_menu(app_state_t *state)
{
	menubar_item(state, "ViewMenuItem", "View",
		(menu_item_config_t[]){
			{
				.element_id = "Settings",
				.icon = (int) state->gui.windows.settings
					? "checkbox-marked"
					: "checkbox-blank-outline",
				.text = "Settings",
				.clicked = on_view_settings_clicked,
			},
		}, 1
	);
}

static void debug_menu(app_state_t *state)
{
	menubar_item(state, "DebugMenuItem", "Debug",
		(menu_item_config_t[]){
		}, 0
	);
}

static void help_menu(app_state_t *state)
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

static void fps_counter(app_state_t *state)
{
	SDL_snprintf(state->gui.timer.text, 8, "%.0f FPS", state->gui.timer.fps);
	shiny_label(state->gui.timer.text, FONT_SIZE_MENU);
}

void menubar(app_state_t *state)
{
	shiny_menubar_begin("Menubar");
	{
		file_menu(state);
		view_menu(state);
		debug_menu(state);
		help_menu(state);

		shiny_h_spacer();

		fps_counter(state);
	}
	shiny_menubar_end();
}
