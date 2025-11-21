include(FetchContent)

FetchContent_Declare(tomlc17
	GIT_REPOSITORY https://github.com/cktan/tomlc17.git
	GIT_TAG R250712
)

message(STATUS "Downloading tomlc17")
FetchContent_MakeAvailable(tomlc17)

add_library(tomlc17 SHARED)

target_sources(tomlc17 PRIVATE
	"${tomlc17_SOURCE_DIR}/src/tomlc17.c"
)

target_include_directories(tomlc17 PUBLIC
	"${tomlc17_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME} PRIVATE tomlc17)