#pragma once

#include "caw/guistate.h"
#include "caw/renderer/clayrenderersdl3.h"

#include "clay.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_init.h>

typedef struct app_state_t
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	struct nk_context *ctx;
	Clay_Arena arena;
	Clay_SDL3RendererData clay;
	SDL_Color bg;
	gui_state_t gui;
	SDL_AppResult result;
} app_state_t;
