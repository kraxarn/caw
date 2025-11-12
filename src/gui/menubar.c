#include "caw/gui/menubar.h"
#include "caw/appstate.h"
#include "caw/guistate.h"
#include "caw/gui/apptheme.h"

#include "clay.h"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_dialog.h>

typedef struct menu_item_config_t
{
	Clay_String text;
	void (*clicked)(app_state_t *);
} menu_item_config_t;

void SDLCALL on_file_opened(void *userdata, const char *const *filelist, int filter)
{
}

Clay_TextElementConfig text_config()
{
	return (Clay_TextElementConfig){
		.fontSize = 12,
		.textColor = app_color_clay(COLOR_FOREGROUND),
	};
}

void menu_item(const menu_item_config_t *item)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.padding = CLAY_PADDING_ALL(12)
		},
	};

	CLAY_AUTO_ID(element)
	{
		CLAY_TEXT(item->text, CLAY_TEXT_CONFIG(text_config()));
	}
}

void menu_items(const menu_item_config_t *items, const size_t count)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_FIXED(200),
			},
		},
		.backgroundColor = app_color_clay(COLOR_WINDOW_BACKGROUND),
	};

	CLAY_AUTO_ID(element)
	{
		for (size_t i = 0; i < count; i++)
		{
			menu_item(items + i);
		}
	}
}

void menu_content(const menu_item_config_t *items, const size_t count)
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
				.top = SIZE_MENUBAR_PADDING + SIZE_GAP,
			},
		},
	};

	CLAY_AUTO_ID(element)
	{
		menu_items(items, count);
	}
}

void on_menubar_item_hover([[maybe_unused]] Clay_ElementId element_id,
	Clay_PointerData pointer_data, intptr_t user_data)
{
	if (pointer_data.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
	{
		const auto state = (app_state_t *) user_data;
		state->gui.windows.menu = true;
	}
}

void menubar_item(app_state_t *state, const Clay_String item_id, const Clay_String text,
	const menu_item_config_t *items, const size_t count)
{
	CLAY(CLAY_SID(item_id))
	{
		CLAY_TEXT(text, CLAY_TEXT_CONFIG(text_config()));
		Clay_OnHover(on_menubar_item_hover, (intptr_t) state);

		if ((int) state->gui.windows.menu && (int) Clay_Hovered())
		{
			menu_content(items, count);
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
			{.text = CLAY_STRING("New..."),},
			{
				.text = CLAY_STRING("Open..."),
				.clicked = on_file_open_clicked,
			},
			{.text = CLAY_STRING("Save"),},
			{.text = CLAY_STRING("Save As..."),},
			{.text = CLAY_STRING("Export..."),},
			{
				.text = CLAY_STRING("Quit"),
				.clicked = on_file_quit_clicked,
			},
		}, 6
	);
}

// enum nk_symbol_type radio_symbol(const int checked)
// {
// 	return checked
// 		? NK_SYMBOL_CIRCLE_SOLID
// 		: NK_SYMBOL_CIRCLE_OUTLINE;
// }

void on_view_settings_clicked(app_state_t *state)
{
	state->gui.windows.settings = (bool) !state->gui.windows.settings;
}

void view_menu(app_state_t *state)
{
	menubar_item(state, CLAY_STRING("ViewMenuItem"), CLAY_STRING("View"),
		(menu_item_config_t[]){
			{.text = CLAY_STRING("Settings"),},
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
			{.text = CLAY_STRING("About..."),},
		}, 1
	);
}

void menubar(app_state_t *state)
{
	const Clay_LayoutConfig layout = {
		.layoutDirection = CLAY_LEFT_TO_RIGHT,
		.sizing = (Clay_Sizing){
			.width = CLAY_SIZING_GROW(0),
			.height = CLAY_SIZING_FIXED(0),
		},
		.padding = CLAY_PADDING_ALL(SIZE_MENUBAR_PADDING),
		.childGap = SIZE_MENUBAR_GAP,
	};

	const Clay_ElementDeclaration element = {
		.layout = layout,
		.backgroundColor = app_color_clay(COLOR_WINDOW_BACKGROUND),
	};

	CLAY(CLAY_ID("Menubar"), element)
	{
		file_menu(state);
		view_menu(state);
		debug_menu(state);
		help_menu(state);
	}
}
