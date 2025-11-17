#include "shiny/element.h"
#include "shiny/internal/color.h"

#include "clay.h"

#include <SDL3/SDL_stdinc.h>

void shiny_element_open(const char *element_id)
{
	const Clay_String str = {
		.isStaticallyAllocated = true,
		.length = SDL_strlen(element_id),
		.chars = element_id
	};
	Clay__OpenElementWithId(CLAY_SID(str));
}

void shiny_element_close()
{
	Clay__CloseElement();
}

void shiny_set_corner_radius(const shiny_corner_radius_t radius)
{
	const Clay_ElementDeclaration element = {
		.cornerRadius = (Clay_CornerRadius){
			.topLeft = radius.top_left,
			.topRight = radius.top_right,
			.bottomLeft = radius.bottom_left,
			.bottomRight = radius.bottom_right,
		},
	};
	Clay__ConfigureOpenElementPtr(&element);
}

void shiny_set_corner_radius_all(const Uint16 all)
{
	const shiny_corner_radius_t radius = {
		.top_left = all,
		.top_right = all,
		.bottom_left = all,
		.bottom_right = all,
	};
	shiny_set_corner_radius(radius);
}

void shiny_set_background_color(const Uint32 color)
{
	const Clay_ElementDeclaration element = {
		.backgroundColor = shiny_color_rgb(color),
	};
	Clay__ConfigureOpenElementPtr(&element);
}

void shiny_set_layout_direction(const shiny_layout_direction_t direction)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.layoutDirection = direction,
		}
	};
	Clay__ConfigureOpenElementPtr(&element);
}

void shiny_set_fixed_width(const float width)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_FIXED(width),
			},
		},
	};
	Clay__ConfigureOpenElementPtr(&element);
}

void shiny_set_fixed_height(const float height)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.height = CLAY_SIZING_FIXED(height),
			},
		},
	};
	Clay__ConfigureOpenElementPtr(&element);
}

void shiny_set_expand_width(const float grow)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.width = CLAY_SIZING_GROW(grow),
			},
		},
	};
	Clay__ConfigureOpenElementPtr(&element);
}

void shiny_set_expand_height(const float grow)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.sizing = (Clay_Sizing){
				.height = CLAY_SIZING_GROW(grow),
			},
		},
	};
	Clay__ConfigureOpenElementPtr(&element);
}

void shiny_set_padding(const shiny_padding_t padding)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.padding = (Clay_Padding){
				.left = padding.left,
				.right = padding.right,
				.top = padding.top,
				.bottom = padding.bottom,
			},
		},
	};
	Clay__ConfigureOpenElementPtr(&element);
}

void shiny_set_padding_all(const Uint16 all)
{
	const shiny_padding_t padding = {
		.left = all,
		.right = all,
		.top = all,
		.bottom = all,
	};
	shiny_set_padding(padding);
}

void shiny_set_child_gap(const Uint16 gap)
{
	const Clay_ElementDeclaration element = {
		.layout = (Clay_LayoutConfig){
			.childGap = gap,
		},
	};
	Clay__ConfigureOpenElementPtr(&element);
}
