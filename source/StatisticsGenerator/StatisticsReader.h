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
			/*@brief StatisticsReaderImpl: a wrapper for a tree reader
			* enabled only to support reading through boost::property_tree::ptree
			*@param path: path to a json file.
			*/
			explicit StatisticsReaderImpl(std::string&& _path);
			
			/*@brief StatisticsReaderImpl: a wrapper for a tree reader
			* enabled only to support reading through boost::property_tree::ptree
			*@param tree: a ptree object, passed directly if already created outside.
			*/
			explicit StatisticsReaderImpl(T<P>&& _tree);
			~StatisticsReaderImpl() = default;
			StatisticsReaderImpl(const StatisticsReaderImpl&) = default;
			StatisticsReaderImpl& operator=(const StatisticsReaderImpl&) = default;
			StatisticsReaderImpl(StatisticsReaderImpl&& _other) noexcept;
			StatisticsReaderImpl& operator=(StatisticsReaderImpl&& _other) noexcept;

			//implementation
			/*@brief GetDataPoints: get all theh data points of a given json file
			* this function supports thread safety
			*@return std::vector<std::pair<std::string, double>>: a container of key, value pair
			* in the same order as read from the file
			*/
			std::vector<std::pair<std::string, double>> GetDataPoints();
			
			/*@brief GetKeyValueDataPoints: get all the data points of a given json file
			* as a key value format; the data is sorted by date
			* this function supports thread safety
			*@return std::map<std::string, double>: a map of key, value pair
			* the data is sorted by key, which is date.
			*/
			std::map<std::string, double> GetKeyValueDataPoints();
	private:
		T<P> treeReader_;
		std::recursive_mutex mutex_;
	};
	#include "StatisticsReader.hpp"
	using StatisticsJsonReader = StatisticsReaderImpl<TreeReader, boost::property_tree::ptree>;
}
#endif // !statsgenerator_statisticsreader_h

