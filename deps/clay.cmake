include(FetchContent)

FetchContent_Declare(clay
	GIT_REPOSITORY https://github.com/kraxarn/clay.git
	GIT_TAG 4d702367116ec734bbda52ad2d09847519db85a4
	SOURCE_SUBDIR ignore
)

message(STATUS "Downloading Clay UI")
FetchContent_MakeAvailable(clay)

target_include_directories(${PROJECT_NAME} PUBLIC
	"${clay_SOURCE_DIR}"
)