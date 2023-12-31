cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME 2DEngine)

project(${PROJECT_NAME})

add_executable(2DEngine 
	src/2DEngine.cpp
	src/renderer/ShaderProgram.cpp
	src/renderer/ShaderProgram.h
	src/renderer/Texture2D.cpp
	src/renderer/Texture2D.h
	src/resources/ResourceManager.cpp
	src/resources/ResourceManager.h
	src/resources/stb_image.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)