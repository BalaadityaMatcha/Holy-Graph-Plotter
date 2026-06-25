cmake_minimum_required(VERSION 3.14)
project(Week2)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Fetch GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# GLAD is located in ../common/glad
add_library(glad ../common/glad/src/glad.c)
target_include_directories(glad PUBLIC ../common/glad/include)

add_executable(opengl_setup main.cpp)
target_link_libraries(opengl_setup PRIVATE glfw glad glm::glm)
