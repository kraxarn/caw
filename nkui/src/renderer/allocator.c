#include "caw/renderer/allocator.h"

// For NK_BUFFER_DEFAULT_INITIAL_SIZE
#include "src/nuklear_internal.h"

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_assert.h>

NK_LIB void *nk_sdl_malloc([[maybe_unused]] nk_handle handle,
	[[maybe_unused]] void *old, const nk_size size)
{
	return SDL_malloc(size);
}

NK_LIB void nk_sdl_free([[maybe_unused]] nk_handle handle, void *ptr)
{
	SDL_free(ptr);
}

NK_API void nk_buffer_init_default(struct nk_buffer *buffer)
{
	struct nk_allocator alloc;
	alloc.userdata.ptr = nullptr;
	alloc.alloc = nk_sdl_malloc;
	alloc.free = nk_sdl_free;

	nk_buffer_init(buffer, &alloc, (nk_size) NK_BUFFER_DEFAULT_INITIAL_SIZE);
}

NK_API nk_bool nk_init_default(struct nk_context *ctx, const struct nk_user_font *font)
{
	struct nk_allocator alloc;
	alloc.userdata.ptr = nullptr;
	alloc.alloc = nk_sdl_malloc;
	alloc.free = nk_sdl_free;

	return nk_init(ctx, &alloc, font);
}

NK_API void nk_font_atlas_init_default(struct nk_font_atlas *atlas)
{
	SDL_assert(atlas != nullptr);
	if (atlas == nullptr)
	{
		return;
	}

	nk_zero_struct(*atlas);
	atlas->temporary.userdata.ptr = nullptr;
	atlas->temporary.alloc = nk_sdl_malloc;
	atlas->temporary.free = nk_sdl_free;
	atlas->permanent.userdata.ptr = nullptr;
	atlas->permanent.alloc = nk_sdl_malloc;
	atlas->permanent.free = nk_sdl_free;
}
