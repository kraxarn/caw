#pragma once

#include <SDL3/SDL_render.h>

SDL_Texture *icon(SDL_Renderer *renderer, const char *name);

const char *icon_data(const char *name, size_t *len);
