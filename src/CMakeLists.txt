add_subdirectory(gui)
add_subdirectory(res)

target_sources(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/ui.c
	${CMAKE_CURRENT_SOURCE_DIR}/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/audiodriver.c
	${CMAKE_CURRENT_SOURCE_DIR}/renderdriver.c
)