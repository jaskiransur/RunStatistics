#define BOOST_TEST_MODULE RunStatsTests
#include <boost\test\unit_test.hpp>
#include <boost\format.hpp>
#include <memory>

#include "Statistics.h"

namespace utf = boost::unit_test;

namespace
{
	const std::string dataPath = "C:\\dev\\repos\\coindesk\\test_data\\data.json";
	constexpr double tolerance = 0.01;
}

namespace
{
	const std::vector<std::pair<std::string, double>> expectedDataBetweenDates={ {"2018-01-09", 14439.4738}, { "2018-01-10", 14890.7225 }, { "2018-01-11", 13287.26 }, { "2018-01-12", 13812.715 }, { "2018-01-13", 14188.785 }, { "2018-01-14", 13619.0288 }, { "2018-01-15", 13585.9013 }, { "2018-01-16", 11348.02 }};
}


BOOST_AUTO_TEST_CASE(check_data_points_between_dates, *boost::unit_test::tolerance(tolerance))
{
	using namespace statsgenerator;

	Statistics stats(dataPath, "2018-01-09", "2018-01-16");
	auto dataPoints = stats.GetDataPoints();
	for (size_t index = 0; index < dataPoints.size(); ++index)
	{
		BOOST_CHECK_MESSAGE(dataPoints[index].second == expectedDataBetweenDates[index].second,
			(boost::format("Data Point Size is %1%, %2%") % dataPoints[index].second %expectedDataBetweenDates[index].second).str());
	}
}

namespace
{
	const std::vector<double> expectedDataPoints{ 13412.4, 14740.8, 15134.7, 15155.2, 16937.2, 17135.8, 16178.5, 14970.4, 14439.5, 14890.7, 13287.3, 13812.7, 14188.8, 13619, 13585.9, 11348, 11141.2, 11250.6, 11514.9, 12759.6 };
}

BOOST_AUTO_TEST_CASE(check_all_data_points, *utf::tolerance(tolerance))
{
	using namespace statsgenerator;

	Statistics stats(dataPath, "2018-01-01", "2018-01-20");
	auto dataPointsAll = stats.GetDataPoints();

	BOOST_REQUIRE(dataPointsAll.size() == size_t(20));
	
	auto dataPoints = stats.GetDataPoints();
	BOOST_CHECK_MESSAGE(dataPoints.size() == size_t(20), 
						(boost::format("Data Point Size is %1%") %dataPoints.size()).str());

	for (size_t i = 0; i<dataPoints.size(); ++i)
	{
		BOOST_CHECK_MESSAGE(dataPoints[i].second == expectedDataPoints[i],
			(boost::format("Data Point Size is %1%, %2%") % dataPoints[i].second %expectedDataPoints[i]).str());
	}
}

BOOST_AUTO_TEST_CASE(check_bad_dates_return_empty)
{
	using namespace statsgenerator;

	Statistics stats(dataPath, "2000-01-01", "2001-01-20");

	auto dataPoints = stats.GetDataPoints();
	BOOST_CHECK_MESSAGE(dataPoints.size() == size_t(0),
		(boost::format("Data Point Size is %1%") % dataPoints.size()).str());
}

BOOST_AUTO_TEST_CASE(check_start_greater_than_end_returns_throws)
{
	using namespace statsgenerator;

	Statistics stats(dataPath, "2018-01-20", "2018-01-01");

	BOOST_CHECK_THROW(stats.GetDataPoints(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(check_highest, *utf::tolerance(tolerance))
{
	using namespace statsgenerator;

	Statistics stats(dataPath);

	auto highest = stats.GetHighest();
	BOOST_CHECK_MESSAGE(highest.second == 17135.8, (boost::format("Highest Value %1% should match 17135.8") % highest.second).str());
}


BOOST_AUTO_TEST_CASE(check_lowest, *utf::tolerance(tolerance))
{
	using namespace statsgenerator;

	Statistics stats(dataPath);

	auto lowest = stats.GetLowest();
	BOOST_CHECK_MESSAGE(lowest.second == 11141.2, (boost::format("Lowest value %1% should match 11141.2") % lowest.second).str());
}


BOOST_AUTO_TEST_CASE(check_mean_data_point, *utf::tolerance(tolerance))
{
	using namespace statsgenerator;

	Statistics stats(dataPath);

	auto mean = stats.GetMeanDataPoint();
	
	BOOST_CHECK_MESSAGE(mean == 13975.2, (boost::format("Mean value %1% should match 13975.2") % mean).str());
}

BOOST_AUTO_TEST_CASE(check_median_data_point, *utf::tolerance(tolerance))
{
	using namespace statsgenerator;
	Statistics stats(dataPath);

	auto median = stats.GetMedianDataPoint();
	BOOST_CHECK_MESSAGE(median == 13287.3, (boost::format("Median value %1% should match 13287.3") % median).str());
}
 
BOOST_AUTO_TEST_CASE(check_std_deviation, *utf::tolerance(tolerance))
{
	using namespace statsgenerator;
	Statistics stats(dataPath);

	auto stddev = stats.GetStandardDevDataPoint();
	BOOST_CHECK_MESSAGE(stddev == 1732.22
	, (boost::format("Std deviation %1% should match 1732.22") % stddev).str());
}