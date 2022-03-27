FILE(GLOB base-sources
        context/context.cpp)

add_library(base-obj ${base-sources})
set_property(TARGET base-obj PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD})