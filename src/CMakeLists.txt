add_subdirectory(window)

target_sources(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainmenubar.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/font.cpp
)