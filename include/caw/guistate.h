#pragma once

#include "clay.h"

#include <stdint.h>

typedef struct gui_settings_state_t
{
	const char *renderer;
	const char *audio_driver;
} gui_settings_state_t;

typedef struct app_state_t app_state_t;

typedef void (*cb_select_callback_t)(app_state_t *state, int index);

typedef struct cb_item_hover_data_t
{
	int index;
	cb_select_callback_t callback;
} cb_item_hover_data_t;

typedef struct gui_window_state_t
{
	bool visible;
	Clay_Vector2 position;
	Clay_Vector2 offset;
	Clay_FloatingAttachPointType attach_point;
} gui_window_state_t;

typedef struct gui_windows_state_t
{
	gui_window_state_t settings;
	Clay_ElementId current_combobox;
	cb_item_hover_data_t current_combobox_item;
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
	uint64_t previous;
	uint64_t dt;
	uint64_t fps_update;
	float fps;
	char text[8];
} gui_timer_state_t;

typedef struct gui_state_t
{
	gui_settings_state_t settings;
	gui_windows_state_t windows;
	gui_timer_state_t timer;
} gui_state_t;
