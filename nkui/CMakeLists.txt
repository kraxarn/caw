cmake_minimum_required(VERSION 3.16)
project(caw LANGUAGES C VERSION 0.0.1)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME})
add_subdirectory(src)

include(../deps/nuklear.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
	"${nuklear_SOURCE_DIR}"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	APP_NAME="${PROJECT_NAME}"
	APP_VERSION="v${PROJECT_VERSION}"
)

# More portable or something, i dunno, it's funny
set_target_properties(${PROJECT_NAME} PROPERTIES
	LINK_FLAGS "-nostdlib"
)

find_package(SDL3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)