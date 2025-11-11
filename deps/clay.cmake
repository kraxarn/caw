include(FetchContent)

FetchContent_Declare(clay
	GIT_REPOSITORY https://github.com/kraxarn/clay.git
	GIT_TAG 9abe80070b15c604dcdbf86c327ae66c3a357545
	SOURCE_SUBDIR ignore
)

message(STATUS "Downloading Clay UI")
FetchContent_MakeAvailable(clay)

target_include_directories(${PROJECT_NAME} PUBLIC
	"${clay_SOURCE_DIR}"
)