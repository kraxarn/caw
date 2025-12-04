#include "caw/renderdriver.h"
#include "caw/logcategory.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_properties.h>

static SDL_PropertiesID props = 0;

static bool update_cache()
{
	props = SDL_CreateProperties();
	if (props == 0)
	{
		SDL_LogWarn(LOG_CATEGORY_GUI, "Render driver cache error: %s", SDL_GetError());
		return false;
	}

	SDL_SetStringProperty(props, "direct3d11", "DirectX 11");
	SDL_SetStringProperty(props, "direct3d12", "DirectX 12");
	SDL_SetStringProperty(props, "direct3d", "DirectX 9");
	SDL_SetStringProperty(props, "metal", "Metal");
	SDL_SetStringProperty(props, "opengl", "OpenGL");
	SDL_SetStringProperty(props, "opengles2", "OpenGL ES 2.0");
	SDL_SetStringProperty(props, "PS2 gsKit", "gsKit");
	SDL_SetStringProperty(props, "VITA gxm", "GXM");
	SDL_SetStringProperty(props, "vulkan", "Vulkan");
	SDL_SetStringProperty(props, "gpu", "GPU API (VK/DX12/MTL)");
	SDL_SetStringProperty(props, "software", "Software");

	return true;
}

const char *render_driver_display_name(const char *name)
{
	if (props == 0 && !update_cache())
	{
		return name;
	}

	return SDL_GetStringProperty(props, name, name);
}
