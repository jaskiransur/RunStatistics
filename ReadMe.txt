Projects:
RunStatistics

RunStatistics.exe --help
--json <path to json file>
--json "C:\Users\jaski\source\JasInTheBox\test_data\data.json"
--j "C:\Users\jaski\source\JasInTheBox\test_data\data.json" --s "2018-01-06" --e "2018-01-17"

--json <path to json file> --start_date <date> --end_date <end date>
--json "C:\Users\jaski\source\JasInTheBox\test_data\data.json" --start_date "2018-01-06" --end_date "2018-01-17"
--j "C:\Users\jaski\source\JasInTheBox\test_data\data.json" --s "2018-01-06" --e "2018-01-17"

Note: network path doesn't work correctly as of now

StatisticsGenerator
This project has the basic framework for reading from a json file
TreeReader.h
base template class for reading a data file
PTreeReaderImpl.hpp
specialized implementation for boost::property_tree::ptree
StatisticsReader.h/.cpp
Wrapper for TreeReader, only one type is enabled for ptree
Statistics.h/.cpp
Implements functions required for RunStatistics

TestStatisticsGenerator
This project has the all the tests

makefile
run cmake from the repository top level path
e.g. C:\Users\jaski\source>cmake coindesk/build coindesk
optional parameter: -G to specify certain version of visual studio


Running tests:
Test must be run in x64 configuration
-Test->Test Settings->Default Processor Architecture->x64
boosttests.runsettings should be loaded to the test run
-Test->Test Settings->Select Test Settings File, and select provided "boosttests.runsettings"
-This should detect the tests; if tests are not detected, it generally means that a dependent dlls are missing.
-If the build failed to copy the dlls, then can be copied from lib\boost_1_63_0\lib64-msvc-14.0\*.dll to build\bin\<Config>\
-The tests, if still undetected can be run using command line
TestStatisticsGenerator.exe --run_test="specific_test"
or 
TestStatisticsGenerator.exe to run all tests