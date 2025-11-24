#pragma once

#include "caw/guistate.h"
#include "caw/settings.h"
#include "caw/renderer/clayrenderersdl3.h"

#include "shiny/font.h"

#include "clay.h"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

typedef struct app_fonts_t
{
	shiny_font_t *body;
} app_fonts_t;

typedef struct app_state_t
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	Clay_Arena arena;
	Clay_SDL3RendererData clay;
	SDL_Color bg;
	settings_t *settings;
	gui_state_t gui;
	SDL_AppResult result;
	app_fonts_t fonts;
} app_state_t;
