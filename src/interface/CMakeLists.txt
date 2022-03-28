FILE(GLOB interface-sources
        smuggler_service_handler.cpp)

add_library(interface-obj ${interface-sources})
set_property(TARGET interface-obj PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD})
