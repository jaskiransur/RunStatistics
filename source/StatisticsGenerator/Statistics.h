#ifndef statsgenerator_statistics_h
#define statsgenerator_statistics_h

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <mutex>
#include <string>
#include <utility>

#include "Config.h"
#include "TreeReader.h"
#include "StatisticsReader.h"


namespace statsgenerator
{
	class LIB_STATS_GENERATOR Statistics
	{
	public:
		explicit Statistics(boost::filesystem::path path);
		explicit Statistics(boost::filesystem::path path, const std::string& startDate, const std::string& endDate);

		Statistics(const Statistics&) = default;
		Statistics& operator=(const Statistics&) = default;
		Statistics(Statistics&&) = default;
		Statistics& operator=(Statistics&&) = default;
		~Statistics() = default;

		//implementation
		/*@brief GetHighest: get highest value from the json file and from
		* within the range of start/end date
		* this function supports thread safety
		*@return std::pair<std::string, double>: a pair of key and value
		*/
		std::pair<std::string, double> GetHighest();
		
		/*@brief GetHighest: get highest value from the json file and from
		* within the range of start/end date
		* this function supports thread safety
		*@return std::pair<std::string, double>: a pair of key and value
		*/
		std::pair<std::string, double> GetLowest();
		
		/*@brief GetDataPoints: get data points from the json file,
		* looks through all data points
		* this function supports thread safety
		*@param startDate[in]: start date, from which to look the data
		*@param endDate[in]: end date, upto which to look the data
		*@return std::vector<std::pair<std::string, double>>: a container of date, datapoint pair
		*/
		std::vector<std::pair<std::string, double>> GetDataPoints();
		
		/*@brief GetMeanDataPoint: get mean point from json file,
		* within the range of start/end date
		* this function supports thread safety
		*@return double: mean value
		*/
		double GetMeanDataPoint();
		
		/*@brief GetMedianDataPoint: get median point from json file,
		* within the range of start/end date
		* this function supports thread safety
		*@return double: median value
		*/
		double GetMedianDataPoint();
		
		/*@brief GetStandardDevDataPoint: get standard deviation from json file,
		* within the range of start/end date
		* this function supports thread safety
		*@return double: standard deviation value
		*/
		double GetStandardDevDataPoint();
	private:
		/*@brief GetDataPoints: get data points from the json file and from
		* within the range of start/end date
		* this function supports thread safety
		*@param startDate[in]: start date, from which to look the data
		*@param endDate[in]: end date, upto which to look the data
		*@return std::vector<std::pair<std::string, double>>: a container of date, datapoint pair
		*/
		std::vector<std::pair<std::string, double>> GetDataPoints(const std::string& startDate, const std::string& endDate);


		StatisticsJsonReader jsonReader_;
		std::string startDate_;
		std::string endDate_;
		std::recursive_mutex mutex_;
	};
}
#endif //statsgenerator_statistics_h