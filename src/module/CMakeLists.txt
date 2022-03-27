FILE(GLOB module-sources
        fetcher/binance_fetcher.cpp
        module.cpp)

add_library(module-obj ${module-sources})
set_property(TARGET module-obj PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD})
