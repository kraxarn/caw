#pragma once

#include <SDL3/SDL_stdinc.h>

typedef struct app_state_t app_state_t;

typedef struct gui_windows_state_t
{
	bool settings;
} gui_windows_state_t;

typedef struct menu_item_config_t
{
	const char *element_id;
	const char *icon;
	const char *text;
	void (*clicked)(app_state_t *);
} menu_item_config_t;

typedef struct menu_item_hover_data_t
{
	menu_item_config_t config;
	app_state_t *state;
} menu_item_hover_data_t;

typedef struct gui_timer_state_t
{
	Uint64 previous;
	Uint64 dt;
	Uint64 fps_update;
	float fps;
	char text[8];
} gui_timer_state_t;

typedef struct gui_state_t
{
	gui_windows_state_t windows;
	gui_timer_state_t timer;
} gui_state_t;
