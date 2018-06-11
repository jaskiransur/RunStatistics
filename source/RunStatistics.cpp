#include <iostream>
//#include "Config.h"
#include "statisticsgenerator/Statistics.h"

int main(int argc, char** argv)
{
	using namespace statsgenerator;
	Statistics stats("C:\\dev\\repos\\coindesk\\data.json");
	std::cout << "data points..." << std::endl;
	for (auto data: stats.GetDataPoints())
		std::cout << data.second<<std::endl;
	std::cout << std::endl;

	auto heighest = stats.GetHighest();
	std::cout << "heighest: "<< heighest.second << std::endl;


	auto lowest = stats.GetLowest();
	std::cout << "lowest: "<<lowest.second << std::endl;
	
	auto mean = stats.GetMeanDataPoint();
	std::cout << "mean: "<< mean<< std::endl;

	auto median = stats.GetMedianDataPoint();
	std::cout << "median: " << median << std::endl;

	auto stddev = stats.GetStandardDevDataPoint();
	std::cout << "standard dev: " << stddev << std::endl;
}