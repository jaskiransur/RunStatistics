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
		Statistics(const Statistics&) = default;
		Statistics& operator=(const Statistics&) = default;
		Statistics(Statistics&&) = default;
		Statistics& operator=(Statistics&&) = default;
		~Statistics() = default;

		std::pair<std::string, double> GetHighest();
		std::pair<std::string, double> GetLowest();
		std::vector<std::pair<std::string, double>> Statistics::GetDataPoints();
		std::vector<double> GetDataPoints(const std::string& startDate, const std::string& endDate);
		double GetMeanDataPoint();
		double GetMedianDataPoint();
		double GetStandardDevDataPoint();
	private:
		StatisticsJsonReader jsonReader_;
		std::recursive_mutex mutex_;
	};
}
#endif //statsgenerator_statistics_h