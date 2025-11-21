#include "caw/renderdriver.h"
#include "caw/logcategory.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_properties.h>

SDL_PropertiesID render_driver_props = 0;

bool update_render_driver_display_name_cache()
{
	render_driver_props = SDL_CreateProperties();
	if (render_driver_props == 0)
	{
		SDL_LogWarn(LOG_CATEGORY_GUI, "Render driver cache error: %s", SDL_GetError());
		return false;
	}

	SDL_SetStringProperty(render_driver_props, "direct3d11", "DirectX 11");
	SDL_SetStringProperty(render_driver_props, "direct3d12", "DirectX 12");
	SDL_SetStringProperty(render_driver_props, "direct3d", "DirectX 9");
	SDL_SetStringProperty(render_driver_props, "metal", "Metal");
	SDL_SetStringProperty(render_driver_props, "opengl", "OpenGL");
	SDL_SetStringProperty(render_driver_props, "opengles2", "OpenGL ES 2.0");
	SDL_SetStringProperty(render_driver_props, "PS2 gsKit", "gsKit");
	SDL_SetStringProperty(render_driver_props, "VITA gxm", "GXM");
	SDL_SetStringProperty(render_driver_props, "vulkan", "Vulkan");
	SDL_SetStringProperty(render_driver_props, "gpu", "GPU API (VK/DX12/MTL)");
	SDL_SetStringProperty(render_driver_props, "software", "Software");

	return true;
}

const char *render_driver_display_name(const char *name)
{
	if (render_driver_props == 0 && !update_render_driver_display_name_cache())
	{
		return name;
	}

	return SDL_GetStringProperty(render_driver_props, name, name);
}
