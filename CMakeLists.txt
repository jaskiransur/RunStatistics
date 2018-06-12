cmake_minimum_required (VERSION 3.9.1)
project (RunStatistics)

set(RUN_STATISTICS_SOURCE_DIR ${PROJECT_SOURCE_DIR})
message(STATUS "Source Path -> " ${RUN_STATISTICS_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "ARCHIVE: -> " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
message(STATUS "LIBRARY: -> " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
message(STATUS "RUNTIME: -> " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


message(STATUS "Configuring projects for coindesk...")
set(BOOST_INCLUDE_DIR ${RUN_STATISTICS_SOURCE_DIR}/lib/boost_1_63_0)
message(STATUS "Boost Include Path -> " ${BOOST_INCLUDE_DIR})

set(BOOST_LIB_DIR ${RUN_STATISTICS_SOURCE_DIR}/lib/boost_1_63_0/lib64-msvc-14.0)

message(STATUS "Solution Path -> " ${PROJECT_BINARY_DIR})

set(RUN_STATISTICS_DIR ${RUN_STATISTICS_SOURCE_DIR}/Source)
message(STATUS "Source RunStatistics Path -> " ${RUN_STATISTICS_DIR})

set(STATISTICS_GENERATOR_DIR ${RUN_STATISTICS_SOURCE_DIR}/Source/StatisticsGenerator)
message(STATUS "Source StatisticsGenerator Path -> " ${STATISTICS_GENERATOR_DIR})

set(STATISTICS_GENERATOR_TESTS_DIR ${RUN_STATISTICS_SOURCE_DIR}/Source/StatisticsGenerator/tests)
message(STATUS "Source StatisticsGenerator Tests Path -> " ${STATISTICS_GENERATOR_TESTS_DIR})

message(STATUS "Binary Path -> " ${PROJECT_BINARY_DIR})
set(BOOST_RELEASE_DLLS	${BOOST_LIB_DIR}/boost_filesystem-vc140-mt-1_63.dll 
	${BOOST_LIB_DIR}/boost_program_options-vc140-mt-1_63.dll 
	${BOOST_LIB_DIR}/boost_system-vc140-mt-1_63.dll 
	${BOOST_LIB_DIR}/boost_unit_test_framework-vc140-mt-1_63.dll)

	
set(BOOST_DEBUG_DLLS
	${BOOST_LIB_DIR}/boost_filesystem-vc140-mt-gd-1_63.dll
    ${BOOST_LIB_DIR}/boost_program_options-vc140-mt-gd-1_63.dll
    ${BOOST_LIB_DIR}/boost_system-vc140-mt-gd-1_63.dll
    ${BOOST_LIB_DIR}/boost_unit_test_framework-vc140-mt-gd-1_63.dll)

set(TEST_FILES ${RUN_STATISTICS_SOURCE_DIR}/boosttests.runsettings
				${RUN_STATISTICS_SOURCE_DIR}/test_data/data.json)

add_subdirectory(${RUN_STATISTICS_DIR})