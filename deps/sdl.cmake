include(FetchContent)

FetchContent_Declare(sdl
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.2.26
)

FetchContent_Declare(sdl_ttf
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
	GIT_TAG release-3.2.2
)

find_package(SDL3 QUIET)
find_package(SDL3_ttf QUIET)
find_package(SDL3_image QUIET)

if (SDL3_FOUND AND SDL3_ttf_FOUND AND SDL3_image_FOUND)
	message(STATUS "Using system SDL")
else ()
	message(STATUS "Downloading SDL")
	FetchContent_MakeAvailable(sdl)
	include(sdl_image.cmake)
	FetchContent_MakeAvailable(sdl_ttf)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE
	SDL3::SDL3
	SDL3_ttf::SDL3_ttf
	SDL3_image::SDL3_image
)

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