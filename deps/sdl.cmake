include(FetchContent)

FetchContent_Declare(sdl
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.2.28
)

find_package(SDL3 QUIET)

if (SDL3_FOUND)
	message(STATUS "Using system sdl3")
else ()
	message(STATUS "Downloading sdl3")
	set(SDL_AUDIO ON)
	set(SDL_CAMERA OFF)
	set(SDL_DIALOG ON)
	set(SDL_GPU OFF)
	set(SDL_HAPTIC OFF)
	set(SDL_HIDAPI OFF)
	set(SDL_JOYSTICK ON)
	set(SDL_POWER OFF)
	set(SDL_RENDER ON)
	set(SDL_SENSOR OFF)
	set(SDL_VIDEO ON)
	FetchContent_MakeAvailable(sdl)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

if (ANDROID)
	set(JAVA_SRC "${sdl_SOURCE_DIR}/android-project/app/src/main/java/org/libsdl/app")
	file(COPY
		"${JAVA_SRC}/HIDDevice.java"
		"${JAVA_SRC}/HIDDeviceBLESteamController.java"
		"${JAVA_SRC}/HIDDeviceManager.java"
		"${JAVA_SRC}/HIDDeviceUSB.java"
		"${JAVA_SRC}/SDL.java"
		"${JAVA_SRC}/SDLActivity.java"
		"${JAVA_SRC}/SDLAudioManager.java"
		"${JAVA_SRC}/SDLControllerManager.java"
		"${JAVA_SRC}/SDLDummyEdit.java"
		"${JAVA_SRC}/SDLInputConnection.java"
		"${JAVA_SRC}/SDLSurface.java"
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/android/app/src/main/java/org/libsdl/app"
	)
endif ()