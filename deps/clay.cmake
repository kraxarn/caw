include(FetchContent)

set(CLAY_INCLUDE_ALL_EXAMPLES OFF)

FetchContent_Declare(clay
	GIT_REPOSITORY https://github.com/nicbarker/clay.git
	GIT_TAG v0.14
)

message(STATUS "Downloading Clay UI")
FetchContent_MakeAvailable(clay)

target_include_directories(${PROJECT_NAME} PUBLIC
	"${clay_SOURCE_DIR}"
)

target_sources(${PROJECT_NAME} PRIVATE
	${clay_SOURCE_DIR}/renderers/SDL3/clay_renderer_SDL3.c
)