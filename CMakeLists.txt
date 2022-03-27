cmake_minimum_required(VERSION 3.19)
project(project_4995 VERSION 1.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE '-O3')

include_directories(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(src/base)
add_subdirectory(src/engine)
add_subdirectory(src/interface)
add_subdirectory(src/module)
add_subdirectory(src/utils)

add_library(core STATIC
        $<TARGET_OBJECTS:base-obj>
        $<TARGET_OBJECTS:engine-obj>
        $<TARGET_OBJECTS:interface-obj>
        $<TARGET_OBJECTS:module-obj>
        $<TARGET_OBJECTS:utils-obj>)

add_executable(project_4995 src/main.cpp)

target_link_libraries(project_4995 core gflags)