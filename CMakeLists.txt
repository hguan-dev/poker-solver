cmake_minimum_required(VERSION 3.20)

project(poker_solver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable profiling if PROFILING is set
option(PROFILING "Enable gprof profiling" OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring with Debug symbols")
    add_compile_options(-g)
    add_link_options(-g)
endif()

if(PROFILING)
    message(STATUS "Enabling gprof profiling")
    add_compile_options(-pg)
    add_link_options(-pg)
endif()

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(GTest REQUIRED)
find_package(pybind11 REQUIRED)
find_package(fmt REQUIRED)

# Define common source files
file(GLOB_RECURSE IMPLEMENTATION_SOURCES src/cards/*.cpp src/game/*.cpp src/players/*.cpp src/util/*.cpp)
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE BENCHMARK_SOURCES benchmarking/*.cpp)
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

# Common include directories
set(COMMON_INCLUDE_DIRS src src/cards src/game src/players src/util ${GTest_INCLUDE_DIRS})

# Common link libraries
set(COMMON_LINK_LIBRARIES pybind11::pybind11 fmt::fmt GTest::gtest GTest::gtest_main pthread)

# Main executable
add_executable(poker_solver ${SOURCES} ${IMPLEMENTATION_SOURCES})
target_include_directories(poker_solver PRIVATE ${COMMON_INCLUDE_DIRS})
target_link_libraries(poker_solver PRIVATE ${COMMON_LINK_LIBRARIES})

# Benchmarking executable
if(BENCHMARK_SOURCES)
    add_executable(poker_solver_benchmarking ${BENCHMARK_SOURCES} ${IMPLEMENTATION_SOURCES})
    target_include_directories(poker_solver_benchmarking PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(poker_solver_benchmarking PRIVATE ${COMMON_LINK_LIBRARIES})
endif()

# Test executable
if(TEST_SOURCES)
    add_executable(poker_solver_tests ${TEST_SOURCES} ${IMPLEMENTATION_SOURCES})
    target_include_directories(poker_solver_tests PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(poker_solver_tests PRIVATE ${COMMON_LINK_LIBRARIES})

    enable_testing()
    add_test(NAME poker_solver_tests COMMAND poker_solver_tests)
else()
    message(WARNING "No test files found in the 'tests/' directory.")
endif()

# Set output directory for all targets
set_target_properties(poker_solver poker_solver_benchmarking poker_solver_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

