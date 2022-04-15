FILE(GLOB module-sources
        fetcher/binance_fetcher.cpp
        fetcher/simple_binance_fetcher.cpp
        module.cpp)

add_library(module-obj ${module-sources})
target_link_libraries(module-obj PRIVATE cpr::cpr)
set_property(TARGET module-obj PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD})
