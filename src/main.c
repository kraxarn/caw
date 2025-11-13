#include "caw/appstate.h"
#include "caw/logcategory.h"
#include "caw/gui/apptheme.h"
#include "caw/gui/tracker.h"
#include "caw/res/fonts.h"

#include "clay.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

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

Clay_Dimensions measure_text(Clay_StringSlice text, Clay_TextElementConfig *config, void *user_data)
{
	TTF_Font **fonts = user_data;
	TTF_Font *font = fonts[config->fontId];
	TTF_SetFontSize(font, config->fontSize);

	int width;
	int height;
	if (!TTF_GetStringSize(font, text.chars, text.length, &width, &height))
	{
		SDL_LogError(LOG_CATEGORY_GUI, "Font error: %s", SDL_GetError());
	}

	return (Clay_Dimensions){(float) width, (float) height};
}

void handle_clay_error(const Clay_ErrorData data)
{
	SDL_LogError(LOG_CATEGORY_GUI, "UI error %d: %s", data.errorType, data.errorText.chars);
}

void clay_state_init(app_state_t *state)
{
	const size_t mem_size = Clay_MinMemorySize();
	state->arena = Clay_CreateArenaWithCapacityAndMemory(mem_size, SDL_malloc(mem_size));

	Clay_Initialize(state->arena,
		(Clay_Dimensions){
			.width = (float) state->gui.out.width,
			.height = (float) state->gui.out.height,
		},
		(Clay_ErrorHandler){
			.errorHandlerFunction = handle_clay_error,
		}
	);

	Clay_SetMeasureTextFunction(measure_text, state->clay.fonts);
}

void clay_state_iterate(app_state_t *state)
{
	Clay_BeginLayout();
	{
		tracker(state);
	}
	Clay_RenderCommandArray commands = Clay_EndLayout();

	SDL_RenderClear(state->clay.renderer);
	SDL_Clay_RenderClayCommands(&state->clay, &commands);
	SDL_RenderPresent(state->clay.renderer);
}

void clay_state_event(const app_state_t *state, const SDL_Event *event)
{
	if (event->type == SDL_EVENT_WINDOW_RESIZED)
	{
		Clay_SetLayoutDimensions((Clay_Dimensions){
			.width = (float) event->window.data1,
			.height = (float) event->window.data2,
		});
		return;
	}

	if (event->type == SDL_EVENT_MOUSE_MOTION
		|| event->type == SDL_EVENT_MOUSE_BUTTON_DOWN
		|| event->type == SDL_EVENT_MOUSE_BUTTON_UP)
	{
		Clay_SetPointerState((Clay_Vector2){
			.x = event->motion.x,
			.y = event->motion.y,
		}, (event->motion.state & SDL_BUTTON_LEFT) > 0);
		return;
	}

	if (event->type == SDL_EVENT_MOUSE_WHEEL)
	{
		Clay_UpdateScrollContainers(true, (Clay_Vector2){
			.x = event->wheel.x,
			.y = event->wheel.y,
		}, (float) state->gui.timer.dt / 1000.F);
		return;
	}

	if (event->type == SDL_EVENT_KEY_DOWN
		&& event->key.key == SDLK_I)
	{
		Clay_SetDebugModeEnabled((bool) !Clay_IsDebugModeEnabled());
		return;
	}
}

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

	if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_LogError(LOG_CATEGORY_CORE, "SDL_Init error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!TTF_Init())
	{
		SDL_LogError(LOG_CATEGORY_CORE, "Font initialisation error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	app_state_t *state = SDL_calloc(1, sizeof(app_state_t));
	if (state == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_CORE, "SDL_malloc error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	state->result = SDL_APP_CONTINUE;
	state->gui.timer.previous = 0;

	constexpr size_t app_info_len = 16;
	char app_info[app_info_len];
	SDL_snprintf(app_info, app_info_len, "%s v%s", APP_NAME, APP_VERSION);

	if (!SDL_CreateWindowAndRenderer(app_info, WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE, &state->window, &state->renderer))
	{
		SDL_free(state);
		SDL_LogError(LOG_CATEGORY_CORE, "SDL_CreateWindowAndRenderer error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	state->clay.renderer = state->renderer;
	state->clay.textEngine = TTF_CreateRendererTextEngine(state->renderer);
	if (state->clay.textEngine == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_CORE, "%s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	state->clay.fonts = SDL_malloc(sizeof(TTF_Font *));
	if (state->clay.fonts == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_CORE, "Font allocation error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_IOStream *font_data = SDL_IOFromConstMem(
		maple_mono_nl_regular_ttf,
		sizeof(maple_mono_nl_regular_ttf)
	);
	state->clay.fonts[0] = TTF_OpenFontIO(font_data, true, 24);
	if (state->clay.fonts[0] == nullptr)
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

	state->bg = app_color_sdl(COLOR_CLEAR);
	SDL_SetRenderDrawColor(state->renderer, state->bg.r, state->bg.g, state->bg.b, state->bg.a);

	clay_state_init(state);

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

	const uint64_t ticks = SDL_GetTicks();
	state->gui.timer.fps = 1000.F / (float) (ticks - state->gui.timer.previous);
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

	nk_state_event(state, event);
	clay_state_event(state, event);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, [[maybe_unused]] SDL_AppResult result)
{
	const auto state = (app_state_t *) appstate;
	if (state != nullptr)
	{
		SDL_free(state->arena.memory);
		SDL_free((void *) state->clay.fonts);

		SDL_DestroyRenderer(state->renderer);
		SDL_DestroyWindow(state->window);
	}

	SDL_free(appstate);
	TTF_Quit();
}
