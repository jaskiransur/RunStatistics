cmake_minimum_required (VERSION 2.6)

message(STATUS "Configuring project RunStatistics...")

include_directories(${RUN_STATSTICS_DIR}
					${STATISTICS_GENERATOR_DIR}
					${BOOST_INCLUDE_DIR})

add_subdirectory (StatisticsGenerator)

set (HEADERS "")

set (SOURCES 
"RunStatistics.cpp"
)


link_directories(${BOOST_LIB_DIR})
set (DEPDENDENT_LIBS StatisticsGenerator)
add_executable(RunStatistics ${HEADERS} ${SOURCES})
set(RUN_STATISTICS_COMPILER_FLAGS "-DBOOST_FILESYSTEM_DYN_LINK -DBOOST_ALL_DYN_LINK")
set_target_properties(RunStatistics PROPERTIES COMPILE_FLAGS ${RUN_STATISTICS_COMPILER_FLAGS})

target_link_libraries (RunStatistics ${DEPDENDENT_LIBS})