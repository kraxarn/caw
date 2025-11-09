package com.kraxarn.caw;

import org.libsdl.app.SDLActivity;

public class CawActivity extends SDLActivity {
	@Override
	protected String[] getLibraries() {
		return new String[] {
			"SDL3",
			"SDL3_ttf",
			"SDL3_image",
			"caw"
		};
	}
}