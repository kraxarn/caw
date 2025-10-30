#pragma once

#include "caw/ui.h"

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

/*
 * Based of:
 * https://github.com/Immediate-Mode-UI/Nuklear/blob/sdl3/demo/sdl3
 * Licenced under the public domain
 */

NK_API struct nk_context *nk_sdl_init(SDL_Window *win, SDL_Renderer *renderer);

NK_API struct nk_font_atlas *nk_sdl_font_stash_begin(const struct nk_context *ctx);

NK_API void nk_sdl_font_stash_end(const struct nk_context *ctx);

NK_API int nk_sdl_handle_event(struct nk_context *ctx, const SDL_Event *event);

NK_API void nk_sdl_render(const struct nk_context *ctx, enum nk_anti_aliasing);

NK_API void nk_sdl_shutdown(struct nk_context *ctx);

NK_API nk_handle nk_sdl_userdata(const struct nk_context *ctx);

NK_API void nk_sdl_set_userdata(const struct nk_context *ctx, nk_handle userdata);
