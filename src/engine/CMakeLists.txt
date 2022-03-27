FILE(GLOB engine-sources
        executor.cpp)

add_library(engine-obj ${engine-sources})
set_property(TARGET engine-obj PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD})
