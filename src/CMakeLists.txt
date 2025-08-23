add_subdirectory(lists)
add_subdirectory(menus)
add_subdirectory(models)
add_subdirectory(synth)
add_subdirectory(widgets)
add_subdirectory(windows)

target_sources(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/font.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/icon.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/iconengine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/maintoolbar.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/iconsizes.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/pianokey.cpp
)