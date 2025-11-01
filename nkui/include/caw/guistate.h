#pragma once

typedef struct gui_output_state_t
{
	int width;
	int height;
} gui_output_state_t;

typedef struct gui_state_t
{
	gui_output_state_t out;
} gui_state_t;
