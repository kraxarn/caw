#pragma once

#define NK_INCLUDE_COMMAND_USERDATA
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_STANDARD_BOOL

#ifndef NK_MEMSET
#include <SDL3/SDL_stdinc.h>
#define NK_MEMSET SDL_memset
#endif

#ifndef NK_BOOL
#define NK_BOOL bool
#endif