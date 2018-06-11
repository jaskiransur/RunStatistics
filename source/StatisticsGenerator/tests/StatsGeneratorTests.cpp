#define BOOST_TEST_MODULE MyTest

#include <boost\test\unit_test.hpp>
#include <memory>
#include <iostream>

#include "TreeReader.h"
#include "StatisticsReader.h"
#include "Config.h"
#include "Statistics.h"

BOOST_AUTO_TEST_CASE( test_scaler_data )
{
	using namespace statsgenerator;
	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>("test_data\data.json");
	auto bpi = treereader.GetVector<double>("bpi");
	auto disclaimer = treereader.GetScaler<std::string>("disclaimer");
	std::cout << disclaimer << std::endl;
	
    BOOST_CHECK(disclaimer == "This data was produced from the CoinDesk Bitcoin Price Index. BPI value data returned as USD.");
}

BOOST_AUTO_TEST_CASE(test_vector_data)
{
	using namespace statsgenerator;
	
	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>("test_data\data.json");
	auto bpi = treereader.GetVector<double>("bpi");
	
	BOOST_CHECK(bpi.size() == 20);
}