#include "caw/appstate.h"
#include "caw/logcategory.h"
#include "caw/gui/apptheme.h"
#include "caw/gui/tracker.h"
#include "caw/renderer/nk_sdl.h"
#include "caw/res/maplemononlregular.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

SDL_AppResult SDL_AppInit([[maybe_unused]] void **appstate,
	[[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
#ifndef NDEBUG
	SDL_SetLogPriorities(SDL_LOG_PRIORITY_DEBUG);
#endif

	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_NAME_STRING, APP_NAME);
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_VERSION_STRING, APP_VERSION);
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_IDENTIFIER_STRING, APP_IDENTIFIER);
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING, APP_CREATOR);
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, APP_TYPE);

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
		SDL_LogError(LOG_CATEGORY_CORE, "SDL_Init error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	const auto state = (app_state_t *) SDL_malloc(sizeof(app_state_t));
	if (state == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_CORE, "SDL_malloc error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE, &state->window, &state->renderer))
	{
		SDL_free(state);
		SDL_LogError(LOG_CATEGORY_CORE, "SDL_CreateWindowAndRenderer error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_SetRenderVSync(state->renderer, 1))
	{
		SDL_LogWarn(LOG_CATEGORY_CORE, "SDL_SetRenderVSync error: %s", SDL_GetError());
	}

	if (!SDL_GetRenderOutputSize(state->renderer, &state->gui.out.width, &state->gui.out.height))
	{
		SDL_LogError(LOG_CATEGORY_GUI, "SDL_GetRenderOutputSize error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_StartTextInput(state->window);

	state->bg = app_color_sdl(COLOR_CLEAR);
	SDL_SetRenderDrawColor(state->renderer, state->bg.r, state->bg.g, state->bg.b, state->bg.a);

	int render_w;
	int render_h;
	int window_w;
	int window_h;

	SDL_GetCurrentRenderOutputSize(state->renderer, &render_w, &render_h);
	SDL_GetWindowSize(state->window, &window_w, &window_h);
	const auto scale_x = (float) render_w / (float) window_w;
	const auto scale_y = (float) render_h / (float) window_h;
	SDL_SetRenderScale(state->renderer, scale_x, scale_y);

	state->ctx = nk_sdl_init(state->window, state->renderer);

	const struct nk_font_config config = nk_font_config(0.F);
	struct nk_font_atlas *atlas = nk_sdl_font_stash_begin(state->ctx);
	struct nk_font *font = nk_font_atlas_add_from_memory(atlas,
		maple_mono_nl_regular_ttf, maple_mono_nl_regular_ttf_len,
		16 * scale_y, &config
	);
	nk_sdl_font_stash_end(state->ctx);

	font->handle.height /= scale_y;
	nk_style_set_font(state->ctx, &font->handle);

	*appstate = state;
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate([[maybe_unused]] void *appstate)
{
	const auto state = (app_state_t *) appstate;
	if (state == nullptr)
	{
		return SDL_APP_FAILURE;
	}

	nk_input_end(state->ctx);

	draw_tracker(state);

	SDL_RenderClear(state->renderer);
	nk_sdl_render(state->ctx, NK_ANTI_ALIASING_OFF);
	SDL_RenderPresent(state->renderer);

	nk_input_begin(state->ctx);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		return SDL_APP_SUCCESS;
	}

	const auto state = (app_state_t *) appstate;
	if (state == nullptr)
	{
		return SDL_APP_FAILURE;
	}

	switch (event->type)
	{
		case SDL_EVENT_WINDOW_RESIZED:
			SDL_LogDebug(LOG_CATEGORY_GUI, "Window resized: %d %d",
				event->window.data1, event->window.data2);
			state->gui.out.width = event->window.data1;
			state->gui.out.height = event->window.data2;
			break;
	}

	nk_sdl_handle_event(state->ctx, event);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, [[maybe_unused]] SDL_AppResult result)
{
	const auto state = (app_state_t *) appstate;
	if (state != nullptr)
	{
		nk_sdl_shutdown(state->ctx);
		SDL_DestroyRenderer(state->renderer);
		SDL_DestroyWindow(state->window);
	}

	SDL_free(appstate);
}
