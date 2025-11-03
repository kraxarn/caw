#pragma once

#include "caw/ui.h"

NK_API void nk_buffer_init_default(struct nk_buffer *buffer);

NK_API nk_bool nk_init_default(struct nk_context *ctx, const struct nk_user_font *font);

NK_API void nk_font_atlas_init_default(struct nk_font_atlas *atlas);