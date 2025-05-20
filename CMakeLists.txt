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
find_package(fmt REQUIRED)

# Define common source files
file(GLOB_RECURSE IMPLEMENTATION_SOURCES src/cards/*.cpp src/game/*.cpp src/players/*.cpp src/mccfr/*.cpp src/utils/*.cpp)
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE BENCHMARK_SOURCES benchmarking/*.cpp)

# Common include directories
set(COMMON_INCLUDE_DIRS src src/cards src/game src/players src/utils src/mccfr ${GTest_INCLUDE_DIRS})

# Common link libraries
set(COMMON_LINK_LIBRARIES fmt::fmt GTest::gtest GTest::gtest_main pthread)

# Main executable
add_executable(poker_solver ${SOURCES} ${IMPLEMENTATION_SOURCES})
target_include_directories(poker_solver PRIVATE ${COMMON_INCLUDE_DIRS})
target_link_libraries(poker_solver PRIVATE ${COMMON_LINK_LIBRARIES})

# Benchmarking executable
if(BENCHMARK_SOURCES)
    add_executable(poker_solver_benchmarking ${BENCHMARK_SOURCES} ${IMPLEMENTATION_SOURCES})
    target_include_directories(poker_solver_benchmarking PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(poker_solver_benchmarking PRIVATE ${COMMON_LINK_LIBRARIES})
    if(APPLE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Enabling sanitizers on macOS for poker_solver_benchmarking")
        target_compile_options(poker_solver_benchmarking PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(poker_solver_benchmarking PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    endif()
endif()

# Find all unit test source files (e.g. tests/unit/*.cpp)
file(GLOB UNIT_TEST_SOURCES tests/unit/*.cpp)

if(UNIT_TEST_SOURCES)
    enable_testing()
    foreach(test_src ${UNIT_TEST_SOURCES})
        # Get the test name from the file name (without extension)
        get_filename_component(test_name ${test_src} NAME_WE)
        add_executable(${test_name} ${test_src} ${IMPLEMENTATION_SOURCES})
        target_include_directories(${test_name} PRIVATE ${COMMON_INCLUDE_DIRS})
        target_link_libraries(${test_name} PRIVATE ${COMMON_LINK_LIBRARIES})
        # Set the runtime output directory for each test executable
        set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
        # Register each test executable with CTest using its name.
        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()
else()
    message(WARNING "No unit test files found in tests/unit.")
endif()

# Set output directory for main and benchmarking executables
set_target_properties(poker_solver PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
if(BENCHMARK_SOURCES)
    set_target_properties(poker_solver_benchmarking PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

