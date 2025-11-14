include(FetchContent)

FetchContent_Declare(clay
	GIT_REPOSITORY https://github.com/kraxarn/clay.git
	GIT_TAG 328cb9c899140e7ac7bf7a0d39f2121f2efba12c
	SOURCE_SUBDIR ignore
)

message(STATUS "Downloading Clay UI")
FetchContent_MakeAvailable(clay)

target_include_directories(${PROJECT_NAME} PUBLIC
	"${clay_SOURCE_DIR}"
)