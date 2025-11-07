include(FetchContent)

FetchContent_Declare(sdl
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.2.26
)

find_package(SDL3 QUIET)

if (SDL3_FOUND)
	message(STATUS "Using system SDL")
else ()
	message(STATUS "Downloading SDL")
	FetchContent_MakeAvailable(sdl)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)