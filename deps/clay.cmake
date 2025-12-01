include(FetchContent)

FetchContent_Declare(clay
	GIT_REPOSITORY https://github.com/kraxarn/clay.git
	GIT_TAG 22f23198db36c98c205ee690adcc27018095cd4a
	SOURCE_SUBDIR ignore
)

message(STATUS "Downloading clay")
FetchContent_MakeAvailable(clay)

target_include_directories(${PROJECT_NAME} PUBLIC
	"${clay_SOURCE_DIR}"
)