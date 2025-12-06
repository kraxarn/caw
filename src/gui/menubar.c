#include "caw/gui/menubar.h"
#include "caw/appstate.h"
#include "caw/guistate.h"
#include "caw/gui/apptheme.h"
#include "caw/res/icons.h"

#include "shiny/menubar.h"
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

static void file_menu(app_state_t *state)
{
	if (shiny_menu_begin("FileMenu", "File", FONT_SIZE_MENU))
	{
		if (shiny_menu_item("New", "New", FONT_SIZE_MENU))
		{
		}

		if (shiny_menu_item("Open", "Open...", FONT_SIZE_MENU))
		{
			const SDL_DialogFileFilter filters[] = {
				{"caw project", "caw"},
			};

			SDL_ShowOpenFileDialog(on_file_opened, nullptr, state->window, filters,
				1, nullptr, false);
		}

		if (shiny_menu_item("Save", "Save", FONT_SIZE_MENU))
		{
		}

		if (shiny_menu_item("SaveAs", "Save As...", FONT_SIZE_MENU))
		{
		}

		if (shiny_menu_item("Export", "Export...", FONT_SIZE_MENU))
		{
		}

		if (shiny_menu_item("Quit", "Quit", FONT_SIZE_MENU))
		{
			state->result = SDL_APP_SUCCESS;
		}
	}
	shiny_menu_end();
}

static void view_menu(app_state_t *state)
{
	if (shiny_menu_begin("ViewMenu", "View", FONT_SIZE_MENU))
	{
		const char *icon_name = (int) state->gui.windows.settings
			? "checkbox-marked"
			: "checkbox-blank-outline";
		SDL_Texture *icon_texture = icon(state->renderer, icon_name);
		const shiny_size_t icon_size = {
			.width = 24,
			.height = 24,
		};
		if (shiny_menu_item_icon("Settings", "Settings", FONT_SIZE_MENU, icon_texture, &icon_size))
		{
			state->gui.windows.settings = (bool) !state->gui.windows.settings;
		}
	}
	shiny_menu_end();
}

static void debug_menu()
{
	if (shiny_menu_begin("DebugMenu", "Debug", FONT_SIZE_MENU))
	{
	}
}

static void help_menu()
{
	if (shiny_menu_begin("HelpMenu", "Help", FONT_SIZE_MENU))
	{
		if (shiny_menu_item("About", "About", FONT_SIZE_MENU))
		{
		}
	}
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
		debug_menu();
		help_menu();

		shiny_h_spacer();

		fps_counter(state);
	}
	shiny_menubar_end();
}
