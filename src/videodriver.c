#include "caw/videodriver.h"
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
		SDL_LogWarn(LOG_CATEGORY_GUI, "Video driver cache failed: %s", SDL_GetError());
		return false;
	}

	SDL_SetStringProperty(props, "cocoa", "Cocoa");
	SDL_SetStringProperty(props, "x11", "X11");
	SDL_SetStringProperty(props, "wayland", "Wayland");
	SDL_SetStringProperty(props, "vivante", "Vivante EGL");
	SDL_SetStringProperty(props, "windows", "Windows");
	SDL_SetStringProperty(props, "haiku", "Haiku");
	SDL_SetStringProperty(props, "uikit", "UIKit");
	SDL_SetStringProperty(props, "android", "Android");
	SDL_SetStringProperty(props, "ps2", "PS2");
	SDL_SetStringProperty(props, "psp", "PSP");
	SDL_SetStringProperty(props, "vita", "Vita");
	SDL_SetStringProperty(props, "n3ds", "N3DS");
	SDL_SetStringProperty(props, "kmsdrm", "KMS/DRM");
	SDL_SetStringProperty(props, "riscos", "RISC OS");
	SDL_SetStringProperty(props, "rpi", "Raspberry Pi");
	SDL_SetStringProperty(props, "emscripten", "Emscripten");
	SDL_SetStringProperty(props, "qnx", "QNX Screen");
	SDL_SetStringProperty(props, "offscreen", "Offscreen");
	SDL_SetStringProperty(props, "dummy", "No video");
	SDL_SetStringProperty(props, "openvr", "OpenVR");

	return true;
}

const char *video_driver_display_name(const char *name)
{
	if (props == 0 && !update_cache())
	{
		return name;
	}

	return SDL_GetStringProperty(props, name, name);
}
