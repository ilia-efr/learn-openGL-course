cmake_minimum_required(VERSION 3.26)
project(learnogl_course)

set(CMAKE_CXX_STANDARD 17)

include_directories(libraries/include)
include_directories(libraries/lib)

add_executable(LearnOpenGL main.cpp glad.c
        Shader.cpp)

target_include_directories(LearnOpenGL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/include)
target_link_directories(LearnOpenGL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/lib)
target_link_libraries(LearnOpenGL PRIVATE glfw3 opengl32 gdi32 user32)

