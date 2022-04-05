add_executable(test_module unittest_module.cpp test_work_queue.cpp test_simple_fetcher.cpp)
target_link_libraries(test_module gtest pthread core cpr)