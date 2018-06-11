#ifndef statsgenerator_statistics_h
#define statsgenerator_statistics_h

#include "Config.h"
#include "TreeReader.h"
#include "StatisticsReader.h"

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <utility>
#include <boost/filesystem.hpp>

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

		std::pair<std::string, double> GetHighest() const;
		std::pair<std::string, double> GetLowest() const;
		std::vector<std::pair<std::string, double>> Statistics::GetDataPoints() const;
		std::vector<double> GetDataPoints(const std::string& startDate, const std::string& endDate) const;
		double GetMeanDataPoint() const;
		double GetMedianDataPoint() const;
		double GetStandardDevDataPoint() const;
	private:
		mutable StatisticsJsonReader jsonReader_;
	};
}
#endif //statsgenerator_statistics_h