cmake_minimum_required (VERSION 3.9.1)

message(STATUS "Configuring StatisticsGenerator...")
set(PROJECT_NAME "StatisticsGenerator")

include_directories(${STATISTICS_GENERATOR_DIR}
					${STATISTICS_GENERATOR_TESTS_DIR}
					${BOOST_INCLUDE_DIR})
					
set(CHILD_HEADERS 
"Config.h"
"TreeReader.h"
"PTreeReaderImpl.hpp"
"StatisticsReader.h"
"StatisticsReader.hpp"
"Statistics.h"
)

set(CHILD_SOURCES 
"Statistics.cpp"
)

link_directories(${BOOST_LIB_DIR})

add_library(${PROJECT_NAME} SHARED ${CHILD_HEADERS} ${CHILD_SOURCES})

set(STATISTICS_GENERATOR_COMPILER_FLAGS "-DBUILDING_STATS_GENERATOR -DBOOST_FILESYSTEM_DYN_LINK -DBOOST_ALL_DYN_LINK /wd4819 /wd4251")

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${STATISTICS_GENERATOR_COMPILER_FLAGS})

message(STATUS "Configuring TestStatisticsGenerator...")

set(TEST_PROJECT_NAME "TestStatisticsGenerator")

set(TESTS_SOURCES 
"tests/StatsReaderTests.cpp"
"tests/StatsGeneratorTests.cpp"
"tests/RunStatsTests.cpp"
)
#set(TESTS_COMPILER_FLAGS "-DBOOST_TEST_DYN_LINK")
set(TESTS_COMPILER_FLAGS "-DBOOST_TEST_DYN_LINK -DBOOST_FILESYSTEM_DYN_LINK -DBOOST_ALL_DYN_LINK /wd4819 /wd4251")

link_directories(${BOOST_LIB_DIR})

add_executable(${TEST_PROJECT_NAME} ${TESTS_SOURCES})
set_target_properties(${TEST_PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${TESTS_COMPILER_FLAGS})
target_link_libraries(${TEST_PROJECT_NAME} ${PROJECT_NAME})