include(FetchContent)

FetchContent_Declare(nuklear
	GIT_REPOSITORY https://github.com/Immediate-Mode-UI/Nuklear.git
	GIT_TAG 4.12.8
)
message(STATUS "Downloading Nuklear UI")
FetchContent_MakeAvailable(nuklear)