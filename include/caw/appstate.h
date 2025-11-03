#pragma once

#include "caw/guistate.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

typedef struct app_state_t
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	struct nk_context *ctx;
	SDL_Color bg;
	gui_state_t gui;
} app_state_t;
