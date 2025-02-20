cmake_minimum_required(VERSION 3.20)

project(poker_solver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring with Debug symbols")
    add_compile_options(-g)
    add_link_options(-g)
endif()

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(GTest REQUIRED)
find_package(pybind11 REQUIRED)
find_package(fmt REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(poker_solver ${SOURCES})

target_include_directories(poker_solver PRIVATE src src/cards src/game src/players)

target_link_libraries(poker_solver PRIVATE pybind11::pybind11 fmt::fmt)

set_target_properties(poker_solver PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
file(GLOB_RECURSE IMPLEMENTATION_SOURCES src/cards/*.cpp src/game/*.cpp src/players/*.cpp src/util/*.cpp)

if(TEST_SOURCES)
    add_executable(poker_solver_tests ${TEST_SOURCES} ${IMPLEMENTATION_SOURCES})
    
    target_include_directories(poker_solver_tests PRIVATE 
        src 
        src/cards 
        src/game 
        src/players 
        src/util
        ${GTest_INCLUDE_DIRS}
    )
    
    target_link_directories(poker_solver_tests PRIVATE ${GTest_LIB_DIRS})

    target_link_libraries(poker_solver_tests PRIVATE 
        GTest::gtest 
        GTest::gtest_main 
        pybind11::pybind11 
        pthread
        fmt::fmt
    )
    
    set_target_properties(poker_solver_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    
    enable_testing()
    add_test(NAME poker_solver_tests COMMAND poker_solver_tests)
else()
    message(WARNING "No test files found in the 'src/tests/' directory.")
endif()

