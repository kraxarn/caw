cmake_minimum_required(VERSION 3.16)
project(caw LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
	Core
	Multimedia
	Quick
	QuickControls2
)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(${PROJECT_NAME}_app)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME}_app PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

include(qml.cmake)
include(deps/mdi.cmake)

target_compile_definitions(${PROJECT_NAME}_app PRIVATE APP_NAME="${PROJECT_NAME}")
target_compile_definitions(${PROJECT_NAME}_app PRIVATE APP_VERSION="v${PROJECT_VERSION}")

# Qt configs
target_compile_definitions(${PROJECT_NAME}_app PRIVATE QT_NO_CAST_FROM_ASCII)
target_compile_definitions(${PROJECT_NAME}_app PRIVATE QT_NO_CAST_TO_ASCII)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(${PROJECT_NAME}_app PRIVATE QT_QML_DEBUG)
endif ()

set_target_properties(${PROJECT_NAME}_app PROPERTIES
	# macOS
	MACOSX_BUNDLE TRUE
	MACOSX_BUNDLE_GUI_IDENTIFIER "com.kraxarn.caw"
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	# Android
	QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res/android"
	QT_ANDROID_VERSION_NAME ${PROJECT_VERSION}
	QT_ANDROID_PACKAGE_NAME "com.kraxarn.caw"
	QT_ANDROID_APP_NAME "Caw"
	QT_ANDROID_APP_ICON "@mipmap/ic_launcher"
	# Windows
	WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}_app PRIVATE
	Qt6::Core
	Qt6::Multimedia
	Qt6::Quick
	Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}_app
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
