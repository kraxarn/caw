include(FetchContent)

FetchContent_Declare(qoi
	GIT_REPOSITORY https://github.com/phoboslab/qoi.git
	GIT_TAG 44b233a95eda82fbd2e39a269199b73af0f4c4c3
)

message(STATUS "Downloading qoi")
FetchContent_MakeAvailable(qoi)

target_include_directories(${PROJECT_NAME} PUBLIC
	"${qoi_SOURCE_DIR}"
)