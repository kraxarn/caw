#include "caw/appstate.h"
#include "caw/logcategory.h"
#include "caw/renderdriver.h"
#include "caw/settings.h"
#include "caw/gui/tracker.h"
#include "caw/res/fonts.h"

#include "shiny/font.h"
#include "shiny/init.h"
#include "shiny/theme.h"
#include "shiny/themekey.h"
#include "shiny/internal/color.h"

#include "clay.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

static constexpr auto window_width = 1280;
static constexpr auto window_height = 800;

void nk_state_event(app_state_t *state, const SDL_Event *event)
{
	switch (event->type)
	{
		case SDL_EVENT_WINDOW_RESIZED:
			SDL_LogDebug(LOG_CATEGORY_GUI, "Window resized: %d %d",
				event->window.data1, event->window.data2);
			state->gui.out.width = event->window.data1;
			state->gui.out.height = event->window.data2;
			break;

		case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
			if (SDL_GetWindowSafeArea(state->window, &state->gui.out.safe_area))
			{
				SDL_LogDebug(LOG_CATEGORY_GUI, "Safe area changed: %d %d %d %d",
					state->gui.out.safe_area.x, state->gui.out.safe_area.y,
					state->gui.out.safe_area.w, state->gui.out.safe_area.h
				);
			}
			break;
	}
}

void clay_state_iterate(app_state_t *state)
{
	Clay_Context *context = shiny_state_clay_context(state->shiny);
	Clay_SetCurrentContext(context);

	SDL_RenderClear(state->renderer);

	shiny_state_render_begin(state->shiny);
	{
		tracker(state);
	}
	shiny_state_render_end(state->shiny);

	SDL_RenderPresent(state->renderer);
}

SDL_AppResult SDL_AppInit([[maybe_unused]] void **appstate,
	[[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
#ifndef NDEBUG
	SDL_SetLogPriorities(SDL_LOG_PRIORITY_DEBUG);
#endif

	// NOLINTBEGIN(*-include-cleaner) The values come from CMake, not a header
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_NAME_STRING, APP_NAME);
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_VERSION_STRING, APP_VERSION);
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_IDENTIFIER_STRING, APP_IDENTIFIER);
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING, APP_CREATOR);
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, APP_TYPE);
	// NOLINTEND(*-include-cleaner)

	if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", SDL_GetError(), nullptr);
		SDL_LogError(LOG_CATEGORY_CORE, "Initialisation failed: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	app_state_t *state = SDL_calloc(1, sizeof(app_state_t));
	if (state == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_CORE, "Allocation failed: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	state->result = SDL_APP_CONTINUE;
	state->gui.timer.previous = 0;

	state->window = SDL_CreateWindow(APP_NAME, window_width, window_height, SDL_WINDOW_RESIZABLE);
	if (state->window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", SDL_GetError(), state->window);
		SDL_LogError(LOG_CATEGORY_CORE, "Window creation failed: %s", SDL_GetError());
		SDL_free(state);
		return SDL_APP_FAILURE;
	}

	state->settings = settings_open();
	while (!settings_ready(state->settings))
	{
		SDL_Delay(1);
	}

	const char *renderer_name = settings_string(state->settings, "render_driver", nullptr);
	state->renderer = SDL_CreateRenderer(state->window, renderer_name);
	if (state->renderer == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_CORE, "Render creation failed: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", SDL_GetError(), state->window);
		SDL_free(state);
		return SDL_APP_FAILURE;
	}

	char *title;
	SDL_asprintf(&title, "%s v%s (%s)",
		APP_NAME, APP_VERSION,
		render_driver_display_name(SDL_GetRendererName(state->renderer))
	);
	SDL_SetWindowTitle(state->window, title);
	SDL_free(title);

	shiny_default_theme();

	state->shiny = shiny_state_create(state->renderer);

	shiny_font_t *font = shiny_font_create(state->renderer, maple_mono_nl_regular_ttf);
	if (font == nullptr || !shiny_state_add_font(state->shiny, font))
	{
		SDL_LogError(LOG_CATEGORY_CORE, "Font error: %s", SDL_GetError());
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

	if (!SDL_GetWindowSafeArea(state->window, &state->gui.out.safe_area))
	{
		SDL_LogError(LOG_CATEGORY_GUI, "SDL_GetWindowSafeArea error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	state->bg = shiny_sdl_theme_color(SHINY_COLOR_CLEAR);
	SDL_SetRenderDrawColor(state->renderer, state->bg.r, state->bg.g, state->bg.b, state->bg.a);

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

	const Uint64 ticks = SDL_GetTicks();
	if (ticks > 1000 && state->gui.timer.fps_update < ticks - 1000)
	{
		state->gui.timer.fps_update = ticks;
		state->gui.timer.fps = 1000.F / (float) (ticks - state->gui.timer.previous);
	}
	state->gui.timer.dt = ticks - state->gui.timer.previous;
	state->gui.timer.previous = ticks;

	clay_state_iterate(state);

	return state->result;
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

	const float delta_time = (float) state->gui.timer.dt / 1000.F;

	nk_state_event(state, event);
	shiny_state_event(state->shiny, delta_time, event);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, [[maybe_unused]] SDL_AppResult result)
{
	const auto state = (app_state_t *) appstate;
	if (state != nullptr)
	{
		settings_close(state->settings);
		shiny_state_destroy(state->shiny);

		SDL_DestroyRenderer(state->renderer);
		SDL_DestroyWindow(state->window);
	}

	SDL_free(appstate);
}
