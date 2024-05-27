cmake_minimum_required(VERSION 3.10)
project(myans)

set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME}
    src/path.cpp
    include/myans/path.h
        src/findupdate.cpp
        include/myans/findupdate.h
        src/solution.cpp
        include/myans/solution.h
        src/list_node.cpp
        include/myans/list_node.h
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

find_package(GTest REQUIRED)
add_executable(${PROJECT_NAME}_test
        test/path_test.cpp
        test/unittest_env.cpp
        test/unittest_env.h
        test/findupdate_test.cpp
        test/solution_test.cpp
)
target_link_libraries(${PROJECT_NAME}_test
    PRIVATE
        ${PROJECT_NAME}
        gtest
        gtest_main
)
