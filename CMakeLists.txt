cmake_minimum_required(VERSION 3.19)
project(caw LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

qt_add_executable(caw WIN32 MACOSX_BUNDLE)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Qt configs
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_NO_CAST_FROM_ASCII)
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_NO_CAST_TO_ASCII)

set_target_properties(${PROJECT_NAME} PROPERTIES
	QT_ANDROID_VERSION_NAME ${PROJECT_VERSION}
	QT_ANDROID_PACKAGE_NAME "com.kraxarn.caw"
	QT_ANDROID_APP_NAME "Caw"
)

include(deps/fontawesome.cmake)
include(resources.cmake)

target_link_libraries(caw PRIVATE
	Qt::Core
	Qt::Widgets
	Qt::Multimedia
)

include(GNUInstallDirs)

install(TARGETS caw
	BUNDLE DESTINATION .
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
	TARGET caw
	OUTPUT_SCRIPT deploy_script
	NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
