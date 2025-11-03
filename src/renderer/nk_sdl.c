#include "caw/renderer/nk_sdl.h"
#include "caw/renderer/allocator.h"

#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_clipboard.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

struct nk_sdl_device
{
	struct nk_buffer cmds;
	struct nk_draw_null_texture tex_null;
	SDL_Texture *font_tex;
};

struct nk_sdl_vertex
{
	float position[2];
	float uv[2];
	float col[4];
};

struct nk_sdl
{
	SDL_Window *win;
	SDL_Renderer *renderer;
	struct nk_sdl_device ogl;
	struct nk_context ctx;
	struct nk_font_atlas atlas;
	nk_handle userdata;
};

NK_API nk_handle nk_sdl_userdata(const struct nk_context *ctx)
{
	SDL_assert(ctx != nullptr);

	const auto sdl = (struct nk_sdl *) ctx->userdata.ptr;
	SDL_assert(sdl != nullptr);

	return sdl->userdata;
}

NK_API void nk_sdl_set_userdata(const struct nk_context *ctx, const nk_handle userdata)
{
	SDL_assert(ctx != nullptr);

	const auto sdl = (struct nk_sdl *) ctx->userdata.ptr;
	SDL_assert(sdl != nullptr);

	sdl->userdata = userdata;
}

NK_INTERN void nk_sdl_device_upload_atlas(const struct nk_context *ctx, const void *image,
	const int width, const int height)
{
	SDL_assert(ctx != nullptr);

	const auto sdl = (struct nk_sdl *) ctx->userdata.ptr;
	SDL_assert(sdl != nullptr);

	if (sdl->ogl.font_tex != nullptr)
	{
		SDL_DestroyTexture(sdl->ogl.font_tex);
		sdl->ogl.font_tex = nullptr;
	}

	const auto texture = SDL_CreateTexture(
		sdl->renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC,
		width, height
	);

	if (texture == nullptr)
	{
		SDL_Log("Error creating texture");
		return;
	}

	SDL_UpdateTexture(texture, nullptr, image, 4 * width);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	sdl->ogl.font_tex = texture;
}

NK_API void nk_sdl_render(const struct nk_context *ctx, enum nk_anti_aliasing aa)
{
	SDL_assert(ctx != nullptr);

	const auto sdl = (struct nk_sdl *) ctx->userdata.ptr;
	SDL_assert(sdl != nullptr);

	SDL_Rect saved_clip;
	int vs = sizeof(struct nk_sdl_vertex);
	size_t vp = NK_OFFSETOF(struct nk_sdl_vertex, position);
	size_t vt = NK_OFFSETOF(struct nk_sdl_vertex, uv);
	size_t vc = NK_OFFSETOF(struct nk_sdl_vertex, col);

	/* convert from the command queue into a draw list and draw to the screen */
	const struct nk_draw_command *cmd;
	struct nk_buffer v_buf;
	struct nk_buffer e_buf;

	/* fill converting configuration */
	struct nk_convert_config config;
	static const struct nk_draw_vertex_layout_element vertex_layout[] = {
		{
			.attribute = NK_VERTEX_POSITION,
			.format = NK_FORMAT_FLOAT,
			.offset = NK_OFFSETOF(struct nk_sdl_vertex, position)
		},
		{
			.attribute = NK_VERTEX_TEXCOORD,
			.format = NK_FORMAT_FLOAT,
			.offset = NK_OFFSETOF(struct nk_sdl_vertex, uv)
		},
		{
			.attribute = NK_VERTEX_COLOR,
			.format = NK_FORMAT_R32G32B32A32_FLOAT,
			.offset = NK_OFFSETOF(struct nk_sdl_vertex, col)
		},
		{NK_VERTEX_LAYOUT_END}
	};

	NK_MEMSET(&config, 0, sizeof(config));
	config.vertex_layout = vertex_layout;
	config.vertex_size = sizeof(struct nk_sdl_vertex);
	config.vertex_alignment = NK_ALIGNOF(struct nk_sdl_vertex)
	;
	config.tex_null = sdl->ogl.tex_null;
	config.circle_segment_count = 22;
	config.curve_segment_count = 22;
	config.arc_segment_count = 22;
	config.global_alpha = 1.0F;
	config.shape_AA = aa;
	config.line_AA = aa;

	/* convert shapes into vertexes */
	nk_buffer_init_default(&v_buf);
	nk_buffer_init_default(&e_buf);
	nk_convert(&sdl->ctx, &sdl->ogl.cmds, &v_buf, &e_buf, &config);

	/* iterate over and execute each draw command */
	auto offset = (const nk_draw_index *) nk_buffer_memory_const(&e_buf);

	const bool clipping_enabled = SDL_RenderClipEnabled(sdl->renderer);
	SDL_GetRenderClipRect(sdl->renderer, &saved_clip);

	nk_draw_foreach(cmd, &sdl->ctx, &sdl->ogl.cmds)
	{
		if (!cmd->elem_count)
		{
			continue;
		}

		SDL_Rect rect;
		rect.x = (int) cmd->clip_rect.x;
		rect.y = (int) cmd->clip_rect.y;
		rect.w = (int) cmd->clip_rect.w;
		rect.h = (int) cmd->clip_rect.h;
		SDL_SetRenderClipRect(sdl->renderer, &rect);

		const void *vertices = nk_buffer_memory_const(&v_buf);

		SDL_RenderGeometryRaw(sdl->renderer,
			cmd->texture.ptr,
			(const float *) ((const nk_byte *) vertices + vp), vs,
			(const SDL_FColor *) ((const nk_byte *) vertices + vc), vs,
			(const float *) ((const nk_byte *) vertices + vt), vs,
			((int) v_buf.needed / vs),
			(void *) offset, (int) cmd->elem_count, 2
		);

		offset += cmd->elem_count;
	}

	SDL_SetRenderClipRect(sdl->renderer, &saved_clip);
	if (!clipping_enabled)
	{
		SDL_SetRenderClipRect(sdl->renderer, nullptr);
	}

	nk_clear(&sdl->ctx);
	nk_buffer_clear(&sdl->ogl.cmds);
	nk_buffer_free(&v_buf);
	nk_buffer_free(&e_buf);
}

static void nk_sdl_clipboard_paste([[maybe_unused]] nk_handle handle, struct nk_text_edit *edit)
{
	const char *text = SDL_GetClipboardText();
	if (text)
	{
		nk_textedit_paste(edit, text, nk_strlen(text));
		SDL_free((void *) text);
	}
}

static void nk_sdl_clipboard_copy([[maybe_unused]] nk_handle handle,
	const char *text, const int len)
{
	if (len <= 0 || text == NULL)
	{
		return;
	}

	char *str = SDL_strndup(text, (size_t) len);
	if (str == nullptr)
	{
		return;
	}

	SDL_SetClipboardText(str);
	SDL_free(str);
}

NK_API struct nk_context *nk_sdl_init(SDL_Window *win, SDL_Renderer *renderer)
{
	SDL_assert(win != nullptr);
	SDL_assert(renderer != nullptr);

	struct nk_sdl *sdl = SDL_malloc(sizeof(struct nk_sdl));
	SDL_assert(sdl != nullptr);
	NK_MEMSET(sdl, 0, sizeof(struct nk_sdl));

	sdl->win = win;
	sdl->renderer = renderer;
	nk_init_default(&sdl->ctx, nullptr);
	sdl->ctx.userdata = nk_handle_ptr((void *) sdl);
	sdl->ctx.clip.copy = nk_sdl_clipboard_copy;
	sdl->ctx.clip.paste = nk_sdl_clipboard_paste;
	sdl->ctx.clip.userdata = nk_handle_ptr(nullptr);
	nk_buffer_init_default(&sdl->ogl.cmds);

	return &sdl->ctx;
}

NK_API struct nk_font_atlas *nk_sdl_font_stash_begin(const struct nk_context *ctx)
{
	SDL_assert(ctx != nullptr);

	const auto sdl = (struct nk_sdl *) ctx->userdata.ptr;
	SDL_assert(sdl != nullptr);

	nk_font_atlas_init_default(&sdl->atlas);
	nk_font_atlas_begin(&sdl->atlas);
	return &sdl->atlas;
}

NK_API void nk_sdl_font_stash_end(const struct nk_context *ctx)
{
	SDL_assert(ctx != nullptr);

	const auto sdl = (struct nk_sdl *) ctx->userdata.ptr;
	SDL_assert(sdl != nullptr);

	int width;
	int height;
	const void *image = nk_font_atlas_bake(&sdl->atlas, &width, &height, NK_FONT_ATLAS_RGBA32);
	SDL_assert(image != nullptr);

	nk_sdl_device_upload_atlas(&sdl->ctx, image, width, height);
	nk_font_atlas_end(&sdl->atlas, nk_handle_ptr(sdl->ogl.font_tex), &sdl->ogl.tex_null);
	if (sdl->atlas.default_font)
	{
		nk_style_set_font(&sdl->ctx, &sdl->atlas.default_font->handle);
	}
}

NK_API int nk_sdl_handle_event(struct nk_context *ctx, const SDL_Event *event)
{
	SDL_assert(ctx != nullptr);
	SDL_assert(event != nullptr);

	switch (event->type)
	{
		case SDL_EVENT_KEY_UP:
		case SDL_EVENT_KEY_DOWN:
		{
			const nk_bool down = event->type == SDL_EVENT_KEY_DOWN;
			const nk_bool ctrl = (event->key.mod & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL)) > 0U;
			const nk_bool ctrl_down = (nk_bool) ((int) down && (int) ctrl);

			switch (event->key.key)
			{
				case SDLK_RSHIFT:
				case SDLK_LSHIFT:
					nk_input_key(ctx, NK_KEY_SHIFT, down);
					break;

				case SDLK_DELETE:
					nk_input_key(ctx, NK_KEY_DEL, down);
					break;

				case SDLK_RETURN:
					nk_input_key(ctx, NK_KEY_ENTER, down);
					break;

				case SDLK_TAB:
					nk_input_key(ctx, NK_KEY_TAB, down);
					break;

				case SDLK_BACKSPACE:
					nk_input_key(ctx, NK_KEY_BACKSPACE, down);
					break;

				case SDLK_HOME:
					nk_input_key(ctx, NK_KEY_TEXT_START, down);
					nk_input_key(ctx, NK_KEY_SCROLL_START, down);
					break;

				case SDLK_END:
					nk_input_key(ctx, NK_KEY_TEXT_END, down);
					nk_input_key(ctx, NK_KEY_SCROLL_END, down);
					break;

				case SDLK_PAGEDOWN:
					nk_input_key(ctx, NK_KEY_SCROLL_DOWN, down);
					break;

				case SDLK_PAGEUP:
					nk_input_key(ctx, NK_KEY_SCROLL_UP, down);
					break;

				case SDLK_A:
					nk_input_key(ctx, NK_KEY_TEXT_SELECT_ALL, ctrl_down);
					break;

				case SDLK_Z:
					nk_input_key(ctx, NK_KEY_TEXT_UNDO, ctrl_down);
					break;

				case SDLK_R:
					nk_input_key(ctx, NK_KEY_TEXT_REDO, ctrl_down);
					break;

				case SDLK_C:
					nk_input_key(ctx, NK_KEY_COPY, ctrl_down);
					break;

				case SDLK_V:
					nk_input_key(ctx, NK_KEY_PASTE, ctrl_down);
					break;

				case SDLK_X:
					nk_input_key(ctx, NK_KEY_CUT, ctrl_down);
					break;

				case SDLK_B:
					nk_input_key(ctx, NK_KEY_TEXT_LINE_START, ctrl_down);
					break;

				case SDLK_E:
					nk_input_key(ctx, NK_KEY_TEXT_LINE_END, ctrl_down);
					break;

				case SDLK_UP:
					nk_input_key(ctx, NK_KEY_UP, down);
					break;

				case SDLK_DOWN:
					nk_input_key(ctx, NK_KEY_DOWN, down);
					break;

				case SDLK_LEFT:
					nk_input_key(ctx, ctrl ? NK_KEY_TEXT_WORD_LEFT : NK_KEY_LEFT, down);
					break;

				case SDLK_RIGHT:
					nk_input_key(ctx, ctrl ? NK_KEY_TEXT_WORD_RIGHT : NK_KEY_RIGHT, down);
					break;
			}
			return 1;
		}

		case SDL_EVENT_MOUSE_BUTTON_UP:
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			const nk_bool down = event->button.down;
			const int btn_x = (int) event->button.x;
			const int btn_y = (int) event->button.y;

			switch (event->button.button)
			{
				case SDL_BUTTON_LEFT:
					nk_input_button(ctx,
						event->button.clicks > 1 ? NK_BUTTON_DOUBLE : NK_BUTTON_LEFT,
						btn_x, btn_y, down
					);
					break;

				case SDL_BUTTON_MIDDLE:
					nk_input_button(ctx, NK_BUTTON_MIDDLE, btn_x, btn_y, down);
					break;
				case SDL_BUTTON_RIGHT:
					nk_input_button(ctx, NK_BUTTON_RIGHT, btn_x, btn_y, down);
					break;
			}
		}
			return 1;

		case SDL_EVENT_MOUSE_MOTION:
			ctx->input.mouse.pos.x = event->motion.x;
			ctx->input.mouse.pos.y = event->motion.y;
			ctx->input.mouse.delta.x = ctx->input.mouse.pos.x - ctx->input.mouse.prev.x;
			ctx->input.mouse.delta.y = ctx->input.mouse.pos.y - ctx->input.mouse.prev.y;
			return 1;

		case SDL_EVENT_TEXT_INPUT:
			nk_glyph glyph;
			SDL_memcpy(glyph, event->text.text, NK_UTF_SIZE);
			nk_input_glyph(ctx, glyph);
			return 1;

		case SDL_EVENT_MOUSE_WHEEL:
			nk_input_scroll(ctx, nk_vec2(event->wheel.x, event->wheel.y));
			return 1;
	}
	return 0;
}

NK_API void nk_sdl_shutdown(struct nk_context *ctx)
{
	SDL_assert(ctx != nullptr);

	const auto sdl = (struct nk_sdl *) ctx->userdata.ptr;
	SDL_assert(sdl != nullptr);

	nk_font_atlas_clear(&sdl->atlas);
	nk_buffer_free(&sdl->ogl.cmds);

	if (sdl->ogl.font_tex != nullptr)
	{
		SDL_DestroyTexture(sdl->ogl.font_tex);
		sdl->ogl.font_tex = nullptr;
	}

	ctx->userdata = nk_handle_ptr(nullptr);
	SDL_free(sdl);
	nk_free(ctx);
}
