add_subdirectory(windows)
add_subdirectory(models)
add_subdirectory(lists)
add_subdirectory(widgets)

target_sources(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/font.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/icon.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/iconengine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainmenubar.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
)