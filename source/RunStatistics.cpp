#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include "statisticsgenerator/Statistics.h"

void RunStats(boost::filesystem::path path)
{
	using namespace statsgenerator;
	Statistics stats(path);
	std::cout << "data points..." << std::endl;
	for (auto data : stats.GetDataPoints())
		std::cout << data.second << std::endl;
	std::cout << std::endl;

	auto heighest = stats.GetHighest();
	std::cout << "heighest: " << heighest.second << std::endl;

	auto lowest = stats.GetLowest();
	std::cout << "lowest: " << lowest.second << std::endl;

	auto mean = stats.GetMeanDataPoint();
	std::cout << "mean: " << mean << std::endl;

	auto median = stats.GetMedianDataPoint();
	std::cout << "median: " << median << std::endl;

	auto stddev = stats.GetStandardDevDataPoint();
	std::cout << "standard dev: " << stddev << std::endl;
}

namespace
{
	const std::string help = "--Help: prints help";
	const std::string json = "--Json: json file to read data from";
	const std::string startDate = "--StartDate: start date for beginning date from";
	const std::string endDate = "--EndDate: end date to stop reading data at";
}

void Help()
{
	std::cout << help << std::endl;
	std::cout << json << std::endl;
	std::cout << startDate << std::endl;
	std::cout << endDate << std::endl;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: as follows:" << std::endl;
		return Help(), 0;
	}

	using namespace boost::program_options;

	std::string jsonFile;
	std::string startDate;
	std::string endDate;

	options_description description{"options"};
	description.add_options()
		("help,h","Help")
		("Json", value<std::string>(&jsonFile)->required(), "Json data file")
		("StartDate", value<std::string>(&startDate), "Start date for data")
		("EndDate", value<std::string>(&endDate), "End date for data");

	//command_line_parser parser{ argc, argv };
	//parser.options(description).allow_unregistered().style(command_line_style::default_style || command_line_style::allow_slash_for_short);
	//parsed_options options = parser.run();

	variables_map varMap;
	//store(options, varMap);
	store(parse_command_line(argc, argv, description), varMap);
	//notify(varMap);

	if ((varMap.count("StartDate") || varMap.count("s")) && 
		(varMap.count("EndDate") || varMap.count("e")) &&
		(varMap.count("Json") || varMap.count("j")))
	{
	}
	else if (varMap.count("Json") || varMap.count("j"))
	{
		auto json = varMap["Json"].as<std::string>();
		RunStats(json);
	}
	else
	{
		//std::cout << "No valid arguments pass" << std::endl;
		Help();
	}
}