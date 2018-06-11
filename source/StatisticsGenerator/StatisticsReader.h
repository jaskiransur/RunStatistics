#ifndef statsgenerator_statisticsreader_h
#define statsgenerator_statisticsreader_h
#include <mutex>
#include <type_traits>
#include <vector>

#include "Config.h"
#include "TreeReader.h"
#include "PTreeReaderImpl.hpp"

namespace statsgenerator
{
	template<template<class> class T, class P, class enable = void>
	class StatisticsReaderImpl
	{
		static_assert(std::is_same<T<P>, TreeReader<boost::property_tree::ptree>>::value, "not implemented");
	};

	template<template<class> class T, class P>
	class StatisticsReaderImpl<T, P, std::enable_if_t<std::is_same<T<P>, TreeReader<boost::property_tree::ptree>>::value>>
	{
		public:
			using value_type = std::decay_t<T<P>>;
			explicit StatisticsReaderImpl(std::string&& _path);
			explicit StatisticsReaderImpl(T<P>&& _tree);
			~StatisticsReaderImpl() = default;
			StatisticsReaderImpl(const StatisticsReaderImpl&) = default;
			StatisticsReaderImpl& operator=(const StatisticsReaderImpl&) = default;
			StatisticsReaderImpl(StatisticsReaderImpl&& _other) noexcept;
			StatisticsReaderImpl& operator=(StatisticsReaderImpl&& _other) noexcept;

			//implementation
			std::vector<std::pair<std::string, double>> GetDataPoints();
			std::map<std::string, double> GetKeyValueDataPoints();
	private:
		T<P> treeReader_;
		std::recursive_mutex mutex_;
	};
	#include "StatisticsReader.hpp"
	using StatisticsJsonReader = StatisticsReaderImpl<TreeReader, boost::property_tree::ptree>;
}
#endif // !statsgenerator_statisticsreader_h

