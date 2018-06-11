#ifndef statsgenerator_treereader_h
#define statsgenerator_treereader_h
#include <boost/property_tree/ptree.hpp>
#include <type_traits>
using namespace std;

namespace statsgenerator
{
	template<class T>
	class TreeReader
	{
		static_assert(std::is_same<typename T::value_type, boost::property_tree::ptree>::value, "Reading data file other than json are not supported.");
	};
}
#include "PTreeReaderImpl.hpp"
#endif // !statsgenerator_treereader_h

