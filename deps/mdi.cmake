include(FetchContent)

FetchContent_Declare(mdi
	GIT_REPOSITORY https://github.com/Templarian/MaterialDesign-SVG.git
	GIT_TAG v7.4.47
)
message(STATUS "Downloading icons")
FetchContent_MakeAvailable(mdi)