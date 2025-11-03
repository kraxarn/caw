#pragma once

typedef struct gui_output_state_t
{
	int width;
	int height;
} gui_output_state_t;

typedef struct gui_settings_state_t
{
	const char *renderer;
	const char *audio_driver;
} gui_settings_state_t;

typedef struct gui_state_t
{
	gui_output_state_t out;
	gui_settings_state_t settings;
} gui_state_t;
