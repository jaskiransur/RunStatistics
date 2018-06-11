
#include <boost\test\unit_test.hpp>
#include <memory>
#include <iostream>

#include "Statistics.h"


BOOST_AUTO_TEST_CASE(test_run_statistics)
{
	using namespace statsgenerator;

	Statistics stats("C:\\dev\\repos\\coindesk\\data.json");
	std::cout << "data points..." << std::endl;

	auto heighest = stats.GetHighest();
	BOOST_CHECK_CLOSE(heighest.second, 17135.8, 0.01);

	auto lowest = stats.GetLowest();
	BOOST_CHECK_CLOSE(lowest.second, 11141.2, 0.01);


	auto mean = stats.GetMeanDataPoint();
	BOOST_CHECK_CLOSE(mean, 13975.2, 0.01);

	auto median = stats.GetMedianDataPoint();
	BOOST_CHECK_CLOSE(median, 13287.3, 0.01);

	auto stddev = stats.GetStandardDevDataPoint();
	BOOST_CHECK_CLOSE(stddev, 1732.22, 0.01);
}
