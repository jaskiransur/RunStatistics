//#define BOOST_TEST_MODULE StatsGeneratorTests

#include <boost\test\unit_test.hpp>
#include <memory>
#include <iostream>

#include "TreeReader.h"
#include "StatisticsReader.h"
#include "Config.h"
#include "Statistics.h"


namespace
{
	const std::string dataPath = "C:\\dev\\repos\\coindesk\\test_data\\data.json";
	constexpr double tolerance = 0.01;
}

BOOST_AUTO_TEST_CASE( test_scaler_data_wrong_type_throws )
{
	using namespace statsgenerator;
	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>(dataPath);
	BOOST_CHECK_THROW(treereader.GetScaler<double>("disclaimer"), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(test_vector_get_double_data_as_string_data_works)
{
	using namespace statsgenerator;
	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>(dataPath);
	BOOST_CHECK(treereader.GetVector<double>("disclaimer").size()== size_t(0));
	BOOST_CHECK(treereader.GetVector<std::string>("bpi").size() == size_t(20));
}

BOOST_AUTO_TEST_CASE(test_times)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>(dataPath);
	auto times = treereader.GetVector<std::string>("time");

	BOOST_CHECK(times.size() == size_t(2));
}

namespace
{
	std::vector<std::pair<std::string, std::string>> expectedTimes{
		{"updated", "Jan 21, 2018 00:03:00 UTC"},
		{ "updatedISO", "2018-01-21T00:03:00+00:00" }
	};
}

BOOST_AUTO_TEST_CASE(test_times_data)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>(dataPath);
	auto times = treereader.GetVector<std::string>("time");
	for (size_t index = 0; index < times.size(); ++index)
	{
		BOOST_CHECK(times[index].first == expectedTimes[index].first);
		BOOST_CHECK(times[index].second == expectedTimes[index].second);
	}
}