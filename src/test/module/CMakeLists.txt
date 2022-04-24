add_executable(test_module unittest_module.cpp test_work_queue.cpp test_simple_fetcher.cpp
        test_iceberg_buy_strategyer.cpp test_billionaire_strategyer.cpp)
target_link_libraries(test_module gtest pthread core cpr)