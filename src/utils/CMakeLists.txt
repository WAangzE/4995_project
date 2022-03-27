FILE(GLOB utils-sources
        reflector.cpp)

add_library(utils-obj ${utils-sources})
set_property(TARGET utils-obj PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD})
