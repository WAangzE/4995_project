find_package(GTest)

if (GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIR})
else ()
    message("Warning: \"Google Test not found\"")
    return()
endif ()

add_subdirectory(module)
add_subdirectory(experiments)