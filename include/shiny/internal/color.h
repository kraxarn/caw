#pragma once

#include "shiny/color.h"
#include "shiny/themekey.h"

#include "clay.h"

#include <SDL3/SDL_pixels.h>

Clay_Color shiny_clay_theme_color(shiny_theme_color_t color);

SDL_Color shiny_sdl_theme_color(shiny_theme_color_t color);
