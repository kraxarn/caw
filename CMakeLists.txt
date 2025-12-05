cmake_minimum_required(VERSION 3.16)
project(caw LANGUAGES C VERSION 0.0.1)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (ANDROID)
	add_library(${PROJECT_NAME} SHARED)
else ()
	add_executable(${PROJECT_NAME})
endif ()

add_subdirectory(src)

include(deps/maple-font.cmake)
include(deps/qoi.cmake)
include(deps/sdl.cmake)

add_subdirectory(deps/shiny)
target_link_libraries(${PROJECT_NAME} PRIVATE shiny)

include(cmake/icons.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	APP_NAME="${PROJECT_NAME}"
	APP_VERSION="${PROJECT_VERSION}"
	APP_IDENTIFIER="com.kraxarn.${PROJECT_NAME}"
	APP_CREATOR="kraxie"
	APP_TYPE="application"
)

# More portable or something, i dunno, it's funny
#set_target_properties(${PROJECT_NAME} PROPERTIES
#	LINK_FLAGS "-nostdlib"
#)

set_target_properties(${PROJECT_NAME} PROPERTIES
	# macOS
	MACOSX_BUNDLE TRUE
	MACOSX_BUNDLE_GUI_IDENTIFIER "com.kraxarn.caw"
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	# Windows
	WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
