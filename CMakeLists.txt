cmake_minimum_required (VERSION 2.6)
project (RunStatistics)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "ARCHIVE: -> " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
message(STATUS "LIBRARY: -> " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
message(STATUS "RUNTIME: -> " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


message(STATUS "Configuring projects for coindesk...")
set(BOOST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/boost_1_63_0)
message(STATUS "Boost Include Path -> " ${BOOST_INCLUDE_DIR})

set(BOOST_LIB_DIR ${PROJECT_SOURCE_DIR}/lib/boost_1_63_0/lib64-msvc-14.0)
message(STATUS "Boost Library Path -> " ${BOOST_LIB_DIR})

message(STATUS "Solution Path -> " ${PROJECT_BINARY_DIR})
message(STATUS "Source Path -> " ${PROJECT_SOURCE_DIR})

set(RUN_STATSTICS_DIR ${PROJECT_SOURCE_DIR}/Source)
message(STATUS "Source RunStatistics Path -> " ${RUN_STATSTICS_DIR})

set(STATISTICS_GENERATOR_DIR ${PROJECT_SOURCE_DIR}/Source/StatisticsGenerator)
message(STATUS "Source StatisticsGenerator Path -> " ${STATISTICS_GENERATOR_DIR})

set(STATISTICS_GENERATOR_TESTS_DIR ${PROJECT_SOURCE_DIR}/Source/StatisticsGenerator/tests)
message(STATUS "Source StatisticsGenerator Tests Path -> " ${STATISTICS_GENERATOR_TESTS_DIR})

message(STATUS "Binary Path -> " ${PROJECT_BINARY_DIR})
add_subdirectory(${RUN_STATSTICS_DIR})