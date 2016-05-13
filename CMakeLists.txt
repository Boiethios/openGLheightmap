project(OpenGL3)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(sources SRC_LIST)

ADD_DEFINITIONS(-std=c++11 -Wall -Wextra)

FILE(GLOB_RECURSE LibFiles "sources/*.hpp")
FILE(GLOB_RECURSE Shaders "data/shaders/*.glsl*")
add_custom_target(headers SOURCES ${LibFiles} ${Shaders})

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} -lGL -lglfw -lGLEW ${CMAKE_DL_LIBS})

