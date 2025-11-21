#include "caw/audiodriver.h"

#include <SDL3/SDL_stdinc.h>

const char *audio_driver_display_name(const char *name)
{
	if (SDL_strcmp(name, "pipewire") == 0)
	{
		return "PipeWire";
	}

	if (SDL_strcmp(name, "pulseaudio") == 0)
	{
		return "PulseAudio";
	}

	if (SDL_strcmp(name, "alsa") == 0)
	{
		return "ALSA";
	}

	if (SDL_strcmp(name, "netbsd") == 0)
	{
		return "NetBSD";
	}

	if (SDL_strcmp(name, "wasapi") == 0)
	{
		return "WASAPI";
	}

	if (SDL_strcmp(name, "directsound") == 0)
	{
		return "DirectSound";
	}

	if (SDL_strcmp(name, "haiku") == 0)
	{
		return "BSoundPlayer";
	}

	if (SDL_strcmp(name, "coreaudio") == 0)
	{
		return "CoreAudio";
	}

	if (SDL_strcmp(name, "openslES") == 0)
	{
		return "OpenSL ES";
	}

	if (SDL_strcmp(name, "ps2") == 0)
	{
		return "PS2";
	}

	if (SDL_strcmp(name, "psp") == 0)
	{
		return "PSP";
	}

	if (SDL_strcmp(name, "vita") == 0)
	{
		return "Vita";
	}

	if (SDL_strcmp(name, "n3ds") == 0)
	{
		return "N3DS";
	}

	if (SDL_strcmp(name, "emscripten") == 0)
	{
		return "Web Audio API";
	}

	if (SDL_strcmp(name, "jack") == 0)
	{
		return "JACK";
	}

	if (SDL_strcmp(name, "dsp") == 0)
	{
		return "OSS";
	}

	if (SDL_strcmp(name, "qsa") == 0)
	{
		return "QNX QSA";
	}

	if (SDL_strcmp(name, "disk") == 0)
	{
		return "Disk";
	}

	if (SDL_strcmp(name, "dummy") == 0)
	{
		return "No audio";
	}

	return name;
}
