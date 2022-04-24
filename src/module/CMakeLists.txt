FILE(GLOB module-sources
        fetcher/binance_fetcher.cpp
        fetcher/simple_binance_fetcher.cpp
        filter/simple_price_filter.cpp
        tailer/simple_price_tailer.cpp
        module.cpp)

add_library(module-obj ${module-sources})
target_link_libraries(module-obj cpr::cpr)
set_property(TARGET module-obj PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD})
