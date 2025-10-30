#pragma once

#define NK_INCLUDE_COMMAND_USERDATA
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING

#ifndef NK_MEMSET
#include <SDL3/SDL_stdinc.h>
#define NK_MEMSET SDL_memset
#endif

#ifndef NK_BOOL
#define NK_BOOL bool
#endif

#include "nuklear.h"
