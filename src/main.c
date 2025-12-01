#include "caw/appstate.h"
#include "caw/logcategory.h"
#include "caw/renderdriver.h"
#include "caw/settings.h"
#include "caw/gui/tracker.h"
#include "caw/renderer/clayrenderersdl3.h"
#include "caw/res/fonts.h"

#include "shiny/font.h"
#include "shiny/theme.h"
#include "shiny/themekey.h"
#include "shiny/internal/color.h"

#include "clay.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

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

Clay_Dimensions measure_text(const Clay_StringSlice text, Clay_TextElementConfig *config, void *user_data)
{
	const auto fonts = (shiny_font_t **) user_data;
	const shiny_font_t *font = fonts[config->fontId];

	Clay_Dimensions dimensions;
	shiny_font_measure_text(font, text.chars, text.length, config->fontSize,
		&dimensions.width, &dimensions.height);

	return dimensions;
}

void handle_clay_error(const Clay_ErrorData data)
{
	SDL_LogError(LOG_CATEGORY_GUI, "UI error %d: %s", data.errorType, data.errorText.chars);
}

void clay_state_init(app_state_t *state)
{
	const size_t mem_size = Clay_MinMemorySize();
	state->arena = Clay_CreateArenaWithCapacityAndMemory(mem_size, SDL_malloc(mem_size));

	state->clay_context = Clay_Initialize(state->arena,
		(Clay_Dimensions){
			.width = (float) state->gui.out.width,
			.height = (float) state->gui.out.height,
		},
		(Clay_ErrorHandler){
			.errorHandlerFunction = handle_clay_error,
		}
	);

	Clay_SetMeasureTextFunction(measure_text, (void *) state->fonts);
}

void clay_state_iterate(app_state_t *state)
{
	Clay_BeginLayout();
	{
		tracker(state);
	}
	Clay_RenderCommandArray commands = Clay_EndLayout();

	SDL_RenderClear(state->clay.renderer);

	// TODO: This is probably not a good way to override font rendering
	for (auto i = 0; i < commands.length; i++)
	{
		Clay_RenderCommand *cmd = Clay_RenderCommandArray_Get(&commands, i);
		if (cmd->commandType == CLAY_RENDER_COMMAND_TYPE_TEXT)
		{
			const Clay_TextRenderData *data = &cmd->renderData.text;
			if (!shiny_font_draw_text(state->fonts[data->fontId], cmd->boundingBox.x, cmd->boundingBox.y,
				data->fontSize, data->stringContents.chars, data->stringContents.length))
			{
				SDL_LogError(LOG_CATEGORY_GUI, "Text draw failed: %s", SDL_GetError());
			}

			continue;
		}

		Clay_RenderCommandArray temp = {
			.capacity = commands.capacity,
			.length = 1,
			.internalArray = cmd,
		};
		SDL_Clay_RenderClayCommands(&state->clay, &temp);
	}

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

	app_state_t *state = SDL_calloc(1, sizeof(app_state_t));
	if (state == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_CORE, "SDL_malloc error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	state->result = SDL_APP_CONTINUE;
	state->gui.timer.previous = 0;

	state->window = SDL_CreateWindow(APP_NAME, window_width, window_height, SDL_WINDOW_RESIZABLE);
	if (state->window == nullptr)
	{
		SDL_free(state);
		SDL_LogError(LOG_CATEGORY_CORE, "Window failed: %s", SDL_GetError());
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
		SDL_LogError(LOG_CATEGORY_CORE, "Renderer failed: %s", SDL_GetError());
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

	state->clay.renderer = state->renderer;

	shiny_default_theme();

	state->fonts = SDL_malloc(sizeof(shiny_font_t *));
	if (state->fonts == nullptr)
	{
		SDL_LogError(LOG_CATEGORY_CORE, "Allocation failed: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	state->fonts[0] = shiny_font_create(state->renderer, maple_mono_nl_regular_ttf);
	if (state->fonts[0] == nullptr)
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

	nk_state_event(state, event);
	clay_state_event(state, event);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, [[maybe_unused]] SDL_AppResult result)
{
	const auto state = (app_state_t *) appstate;
	if (state != nullptr)
	{
		settings_close(state->settings);

		shiny_font_destroy(state->fonts[0]);
		SDL_free((void *) state->fonts);

		SDL_free(state->arena.memory);

		SDL_DestroyRenderer(state->renderer);
		SDL_DestroyWindow(state->window);
	}

	SDL_free(appstate);
}
