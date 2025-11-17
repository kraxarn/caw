#pragma once

#include <SDL3/SDL_stdinc.h>

typedef enum shiny_layout_direction_t
{
	SHINY_LEFT_TO_RIGHT,
	SHINY_TOP_TO_BOTTOM,
} shiny_layout_direction_t;

typedef struct shiny_padding_t
{
	Uint16 left;
	Uint16 right;
	Uint16 top;
	Uint16 bottom;
} shiny_padding_t;

typedef struct shiny_corner_radius_t
{
	Uint16 top_left;
	Uint16 top_right;
	Uint16 bottom_left;
	Uint16 bottom_right;
} shiny_corner_radius_t;

void shiny_element_open(const char *element_id);

void shiny_element_close();

// Element

void shiny_set_corner_radius(shiny_corner_radius_t radius);

void shiny_set_corner_radius_all(Uint16 all);

void shiny_set_background_color(Uint32 color);

// Layout

void shiny_set_layout_direction(shiny_layout_direction_t direction);

void shiny_set_fixed_width(float width);

void shiny_set_fixed_height(float height);

void shiny_set_expand_width(float grow);

void shiny_set_expand_height(float grow);

void shiny_set_padding(shiny_padding_t padding);

void shiny_set_padding_all(Uint16 all);

void shiny_set_child_gap(Uint16 gap);
