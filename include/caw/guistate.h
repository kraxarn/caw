#pragma once

#include "clay.h"

#include <stdint.h>
#include <SDL3/SDL_rect.h>

typedef struct gui_output_state_t
{
	int width;
	int height;
	SDL_Rect safe_area;
} gui_output_state_t;

typedef struct gui_settings_state_t
{
	const char *renderer;
	const char *audio_driver;
} gui_settings_state_t;

typedef struct gui_windows_state_t
{
	bool settings;
} gui_windows_state_t;

typedef struct app_state_t app_state_t;

typedef struct menu_item_config_t
{
	const char *icon;
	Clay_String text;
	void (*clicked)(app_state_t *);
} menu_item_config_t;

typedef struct menu_item_hover_data_t
{
	menu_item_config_t config;
	app_state_t *state;
} menu_item_hover_data_t;

typedef struct gui_menu_state_t
{
	bool visible;
	Clay_ElementId current;
	menu_item_hover_data_t current_item;
} gui_menu_state_t;

typedef struct gui_timer_state_t
{
	uint64_t previous;
	uint64_t dt;
	uint64_t fps_update;
	float fps;
	char text[8];
} gui_timer_state_t;

typedef struct gui_state_t
{
	gui_output_state_t out;
	gui_settings_state_t settings;
	gui_windows_state_t windows;
	gui_menu_state_t menu;
	gui_timer_state_t timer;
} gui_state_t;
