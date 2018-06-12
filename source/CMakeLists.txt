cmake_minimum_required (VERSION 3.9.1)

message(STATUS "Configuring project RunStatistics...")

include_directories(${RUN_STATISTICS_DIR}
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

#variable not set always
#if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
foreach(BOOST_DEBUG_DLL ${BOOST_DEBUG_DLLS})
	add_custom_command(
			TARGET RunStatistics POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
					${BOOST_DEBUG_DLL}
					${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/)
endforeach(BOOST_DEBUG_DLL)
#endif(CMAKE_BUILD_TYPE STREQUAL "DEBUG")

#variable not set always
#if(CMAKE_BUILD_TYPE STREQUAL "RELEASE")
foreach(BOOST_RELEASE_DLL ${BOOST_RELEASE_DLLS})
	add_custom_command(
			TARGET RunStatistics POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
					${BOOST_RELEASE_DLL}
					${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/)
endforeach(BOOST_RELEASE_DLL)
#endif(CMAKE_BUILD_TYPE STREQUAL "RELEASE")
