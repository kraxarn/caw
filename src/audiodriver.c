#include "caw/audiodriver.h"
#include "caw/logcategory.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_properties.h>

SDL_PropertiesID audio_driver_props = 0;

bool update_audio_driver_display_name_cache()
{
	audio_driver_props = SDL_CreateProperties();
	if (audio_driver_props == 0)
	{
		SDL_LogWarn(LOG_CATEGORY_GUI, "Render driver cache error: %s", SDL_GetError());
		return false;
	}

	SDL_SetStringProperty(audio_driver_props, "pipewire", "PipeWire");
	SDL_SetStringProperty(audio_driver_props, "pulseaudio", "PulseAudio");
	SDL_SetStringProperty(audio_driver_props, "alsa", "ALSA");
	SDL_SetStringProperty(audio_driver_props, "netbsd", "NetBSD");
	SDL_SetStringProperty(audio_driver_props, "wasapi", "WASAPI");
	SDL_SetStringProperty(audio_driver_props, "directsound", "DirectSound");
	SDL_SetStringProperty(audio_driver_props, "haiku", "BSoundPlayer");
	SDL_SetStringProperty(audio_driver_props, "coreaudio", "CoreAudio");
	SDL_SetStringProperty(audio_driver_props, "openslES", "OpenSL ES");
	SDL_SetStringProperty(audio_driver_props, "ps2", "PS2");
	SDL_SetStringProperty(audio_driver_props, "psp", "PSP");
	SDL_SetStringProperty(audio_driver_props, "vita", "Vita");
	SDL_SetStringProperty(audio_driver_props, "n3ds", "N3DS");
	SDL_SetStringProperty(audio_driver_props, "emscripten", "Web Audio API");
	SDL_SetStringProperty(audio_driver_props, "jack", "JACK");
	SDL_SetStringProperty(audio_driver_props, "dsp", "OSS");
	SDL_SetStringProperty(audio_driver_props, "qsa", "QNX QSA");
	SDL_SetStringProperty(audio_driver_props, "disk", "Disk");
	SDL_SetStringProperty(audio_driver_props, "dummy", "No audio");

	return true;
}

const char *audio_driver_display_name(const char *name)
{
	if (audio_driver_props == 0 && !update_audio_driver_display_name_cache())
	{
		return name;
	}

	return SDL_GetStringProperty(audio_driver_props, name, name);
}
