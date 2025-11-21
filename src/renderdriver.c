#include "caw/renderdriver.h"

#include <SDL3/SDL_stdinc.h>

const char *render_driver_display_name(const char *name)
{
	if (SDL_strcmp(name, "direct3d11") == 0)
	{
		return "DirectX 11";
	}

	if (SDL_strcmp(name, "direct3d12") == 0)
	{
		return "DirectX 12";
	}

	if (SDL_strcmp(name, "direct3d") == 0)
	{
		return "DirectX 9";
	}

	if (SDL_strcmp(name, "metal") == 0)
	{
		return "Metal";
	}

	if (SDL_strcmp(name, "opengl") == 0)
	{
		return "OpenGL";
	}

	if (SDL_strcmp(name, "opengles2") == 0)
	{
		return "OpenGL ES 2.0";
	}

	if (SDL_strcmp(name, "PS2 gsKit") == 0)
	{
		return "gsKit";
	}

	if (SDL_strcmp(name, "PSP") == 0)
	{
		return "PSP";
	}

	if (SDL_strcmp(name, "VITA gxm") == 0)
	{
		return "GXM";
	}

	if (SDL_strcmp(name, "vulkan") == 0)
	{
		return "Vulkan";
	}

	if (SDL_strcmp(name, "gpu") == 0)
	{
		return "GPU API (VK/DX12/MTL)";
	}

	if (SDL_strcmp(name, "software") == 0)
	{
		return "Software";
	}

	return name;
}
