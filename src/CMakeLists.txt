add_subdirectory(models)

target_sources(${PROJECT_NAME}_app PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/apptheme.cpp
)