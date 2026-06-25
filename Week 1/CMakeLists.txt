cmake_minimum_required(VERSION 3.10)
project(Week1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tools_demo main.cpp)

# Enable sanitizers for debug builds if using GCC/Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(tools_demo PRIVATE -Wall -Wextra -g -fsanitize=address)
    target_link_libraries(tools_demo PRIVATE -fsanitize=address)
endif()
