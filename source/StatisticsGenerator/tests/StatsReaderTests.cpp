#include <boost\test\unit_test.hpp>
#include <boost\property_tree\ptree.hpp>
#include "TreeReader.h"


namespace
{
	const std::string dataPath = ".\\data.json";
	constexpr double tolerance = 0.01;
}

BOOST_AUTO_TEST_CASE(bad_path_throws)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader("badfile");
	BOOST_CHECK_THROW(treeReader.GetScaler<std::string>("disclaimer"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(bad_key_scaler_throws)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader(dataPath);

	BOOST_CHECK_THROW(treeReader.GetScaler<std::string>("badkey"), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(bad_key_vector_throws)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader(dataPath);

	BOOST_CHECK_THROW(treeReader.GetVector<double>("badkey"), std::runtime_error);
}
BOOST_AUTO_TEST_CASE(bad_key_kevalue_throws)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader(dataPath);

	BOOST_CHECK_THROW(treeReader.GetKeyValues<double>("badkey"), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(test_scaler_data)
{
	using namespace statsgenerator;
	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>(dataPath);
	auto disclaimer = treereader.GetScaler<std::string>("disclaimer");
	
	BOOST_CHECK(disclaimer == "This data was produced from the CoinDesk Bitcoin Price Index. BPI value data returned as USD.");
}

BOOST_AUTO_TEST_CASE(test_vector_data)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>(dataPath);
	auto bpi = treereader.GetVector<double>("bpi");

	BOOST_CHECK(bpi.size() == size_t(20));
}

BOOST_AUTO_TEST_CASE(test_keyvalue_data)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>(dataPath);
	auto bpi = treereader.GetKeyValues<double>("bpi");

	BOOST_CHECK(bpi.size() == size_t(20));
}

BOOST_AUTO_TEST_CASE(test_assignment_tree_reader)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader(dataPath);
	auto treereaderCopy = treeReader;
	auto disclaimer = treereaderCopy.GetScaler<std::string>("disclaimer");
	BOOST_CHECK(disclaimer == "This data was produced from the CoinDesk Bitcoin Price Index. BPI value data returned as USD.");
	
	auto bpiVector = treereaderCopy.GetVector<double>("bpi");
	BOOST_CHECK(bpiVector.size() == size_t(20));

	auto bpiMap = treereaderCopy.GetKeyValues<double>("bpi");
	BOOST_CHECK(bpiMap.size() == size_t(20));
}

BOOST_AUTO_TEST_CASE(test_copy_tree_reader)
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treeReader(dataPath);
	auto treereaderCopy(treeReader);

	auto disclaimer = treereaderCopy.GetScaler<std::string>("disclaimer");
	BOOST_CHECK(disclaimer == "This data was produced from the CoinDesk Bitcoin Price Index. BPI value data returned as USD.");

	auto bpiVector = treereaderCopy.GetVector<double>("bpi");
	BOOST_CHECK(bpiVector.size() == size_t(20));
	
	auto bpiMap = treereaderCopy.GetKeyValues<double>("bpi");
	BOOST_CHECK(bpiMap.size() == size_t(20));
}

BOOST_AUTO_TEST_CASE(test_vector_keyvalue_data_consistency, *boost::unit_test::tolerance(0.001))
{
	using namespace statsgenerator;

	TreeReader<boost::property_tree::ptree> treereader = TreeReader<boost::property_tree::ptree>(dataPath);
	auto bpiVector = treereader.GetVector<double>("bpi");

	auto bpiMap = treereader.GetKeyValues<double>("bpi");

	BOOST_CHECK(bpiVector.size() == size_t(20));
	BOOST_CHECK(bpiMap.size() == size_t(20));

	for (auto&pair : bpiVector)
	{
		BOOST_CHECK(pair.second == bpiMap[pair.first]);
	}
}