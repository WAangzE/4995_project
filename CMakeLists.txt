cmake_minimum_required(VERSION 3.16)
project(burglar VERSION 1.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE '-O3')

# requirements
find_package(gflags REQUIRED)
find_package(Boost 1.71 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# add cpr library for http requests
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 21f42cf882d0b7e5ae9e3434574fc47e187728de)
FetchContent_MakeAvailable(cpr)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(src/base)
add_subdirectory(src/engine)
add_subdirectory(src/interface)
add_subdirectory(src/module)
add_subdirectory(src/utils)

add_library(core STATIC
        $<TARGET_OBJECTS:base-obj>
        $<TARGET_OBJECTS:interface-obj>
        $<TARGET_OBJECTS:module-obj>
        $<TARGET_OBJECTS:utils-obj>)

add_executable(burglar
        src/main.cpp)
target_link_libraries(burglar core gflags cpr::cpr)

add_subdirectory(src/test)
