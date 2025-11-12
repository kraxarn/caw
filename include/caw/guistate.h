#pragma once

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
	bool menu;
	bool settings;
} gui_windows_state_t;

typedef struct gui_timer_state_t
{
	uint64_t previous;
	uint64_t dt;
} gui_timer_state_t;

typedef struct gui_state_t
{
	gui_output_state_t out;
	gui_settings_state_t settings;
	gui_windows_state_t windows;
	gui_timer_state_t timer;
} gui_state_t;
