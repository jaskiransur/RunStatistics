cmake_minimum_required (VERSION 2.6)

message(STATUS "Configuring StatisticsGenerator...")

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
add_library(StatisticsGenerator SHARED ${CHILD_HEADERS} ${CHILD_SOURCES})
set(STATISTICS_GENERATOR_COMPILER_FLAGS "-DBUILDING_STATS_GENERATOR -DBOOST_FILESYSTEM_DYN_LINK -DBOOST_ALL_DYN_LINK")
set_target_properties(StatisticsGenerator PROPERTIES COMPILE_FLAGS ${STATISTICS_GENERATOR_COMPILER_FLAGS})

message(STATUS "Configuring TestStatisticsGenerator...")
set(TESTS_SOURCES 
"tests/StatsReaderTests.cpp"
"tests/StatsGeneratorTests.cpp"
"tests/RunStatsTests.cpp"
)
#set(TESTS_COMPILER_FLAGS "-DBOOST_TEST_DYN_LINK")
set(TESTS_COMPILER_FLAGS "-DBOOST_TEST_DYN_LINK -DBOOST_FILESYSTEM_DYN_LINK -DBOOST_ALL_DYN_LINK")

link_directories(${BOOST_LIB_DIR})

add_executable(TestStatisticsGenerator ${TESTS_SOURCES})
set_target_properties(TestStatisticsGenerator PROPERTIES COMPILE_FLAGS ${TESTS_COMPILER_FLAGS})
target_link_libraries(TestStatisticsGenerator StatisticsGenerator)