#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include "statisticsgenerator/Statistics.h"

void RunStats(boost::filesystem::path path, const std::string& startDate, const std::string& endDate)
{
	using namespace statsgenerator;
	Statistics stats(path, startDate, endDate);
	
	auto highest = stats.GetHighest();
	std::cout << (boost::format("Highest data point- date: %1%, data point: %2%") % highest.first %highest.second).str() << std::endl;

	auto lowest = stats.GetLowest();
	std::cout << (boost::format("Lowest data point- date: %1%, data point: %2%") % lowest.first %lowest.second).str() << std::endl;

	auto dataPoints = stats.GetDataPoints();
	std::cout << (boost::format("Data points size between- start date: %1%, end data %2% is %3%") 
					% dataPoints.begin()->first %dataPoints.rbegin()->first %dataPoints.size()).str()<< std::endl;

	auto mean = stats.GetMeanDataPoint();
	std::cout << "mean: " << mean << std::endl;

	auto median = stats.GetMedianDataPoint();
	std::cout << "median: " << median << std::endl;

	auto stddev = stats.GetStandardDevDataPoint();
	std::cout << "standard dev: " << stddev << std::endl;
}

namespace
{
	const std::string help = "--help or --h: prints help";
	const std::string json = "--json --j: json file to read data from";
	const std::string startDate = "--start_date or --s: start date for beginning date from";
	const std::string endDate = "--end_date or --e: end date to stop reading data at";
}

void Help()
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
	std::cout << help << std::endl;
	std::cout << json << std::endl;
	std::cout << startDate << std::endl;
	std::cout << endDate << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: as follows:" << std::endl;
		return Help(), 0;
	}

	using namespace boost::program_options;

	options_description description{"options"};
	try
	{
		description.add_options()
			("help,h", "Help")
			("json,j", value<std::string>()->required(), "Json data file")
			("start_date,s", value<std::string>(), "Start date for data")
			("end_date,e", value<std::string>(), "End date for data");
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return Help(), 0;
	}
	
	variables_map varMap;
	store(parse_command_line(argc, argv, description), varMap);
	
	if ((varMap.count("start_date") || varMap.count("s")) && 
		(varMap.count("end_date") || varMap.count("e")) &&
		(varMap.count("json") || varMap.count("j")))
	{
		auto json = varMap["json"].as<std::string>();
		auto startDate = varMap["start_date"].as<std::string>();
		auto endDate = varMap["end_date"].as<std::string>();

		try
		{
			RunStats(json, startDate, endDate);
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
			return Help(), 0;
		}
	}
	else if ((varMap.count("start_date") || varMap.count("s")) &&
		(varMap.count("end_date") || varMap.count("e")) &&
		(varMap.count("json")==0 || varMap.count("j")==0))
	{
		auto json_path = "https://api.coindesk.com/v1/bpi/historical/close.json";
		auto startDate = varMap["start_date"].as<std::string>();
		auto endDate = varMap["end_date"].as<std::string>();
		try
		{
			RunStats(json_path, startDate, endDate);
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
			return Help(), 0;
		}
	}
	else if (varMap.count("json") || varMap.count("j"))
	{
		auto json = varMap["json"].as<std::string>();
		try
		{
			RunStats(json, "", "");
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
			return Help(), 0;
		}
	}
	else
	{
		Help();
	}
}