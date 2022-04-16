FILE(GLOB module-sources
        fetcher/binance_fetcher.cpp
        fetcher/simple_binance_fetcher.cpp
        strategyer/basic_strategyer.cpp
        strategyer/iceberg_buy_strategyer.cpp
        module.cpp)

add_library(module-obj ${module-sources})
target_link_libraries(module-obj PRIVATE cpr::cpr)
set_property(TARGET module-obj PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD})
