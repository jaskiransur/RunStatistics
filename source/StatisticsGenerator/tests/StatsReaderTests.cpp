
#include <boost\test\unit_test.hpp>
#include <boost\property_tree\ptree.hpp>
#include "TreeReader.h"

BOOST_AUTO_TEST_CASE(bad_path_throws)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader("badfile");
	BOOST_CHECK_THROW(treeReader.GetScaler<std::string>("disclaimer"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(bad_key_scaler_throws)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader("test_data\data.json");

	BOOST_CHECK_THROW(treeReader.GetScaler<std::string>("badkey"), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(bad_key_vector_throws)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader("test_data\data.json");

	BOOST_CHECK_THROW(treeReader.GetVector<double>("bpi"), std::runtime_error);
}