enable_testing()

find_package(GTest CONFIG REQUIRED)

set(TEST_SOURCES
        app_test.cpp
        request_test.cpp
)

add_executable(expresscpp_tests ${TEST_SOURCES})

target_link_libraries(expresscpp_tests
        PRIVATE
        expresscpp
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME expresscpp_tests COMMAND expresscpp_tests)
