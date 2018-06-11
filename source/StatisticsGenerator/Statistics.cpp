#include "Statistics.h"
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

#include "statisticsReader.h"

using statsgenerator::Statistics;

Statistics::Statistics(std::string&& path)
	:jsonReader_(std::move(path))
{

}

std::pair<std::string, double> Statistics::GetHighest() const
{
	auto dataPoints = jsonReader_.GetDataPoints();
	
	auto it = std::max_element(dataPoints.cbegin(), dataPoints.cend(),
		[](const decltype(dataPoints)::value_type& leftPair, const decltype(dataPoints)::value_type& rightPair)
	{
		return leftPair.second < rightPair.second;
	});
	return *it;
}

std::pair<std::string, double> Statistics::GetLowest() const
{
	auto dataPoints = jsonReader_.GetDataPoints();

	auto it = std::min_element(dataPoints.cbegin(), dataPoints.cend(),
		[](const decltype(dataPoints)::value_type& leftPair, const decltype(dataPoints)::value_type& rightPair)
	{
		return leftPair.second < rightPair.second;
	});
	return *it;
}

std::vector<std::pair<std::string, double>> Statistics::GetDataPoints() const
{
	return jsonReader_.GetDataPoints();
}

std::vector<double> Statistics::GetDataPoints(const std::string & startDate, const std::string & endDate) const
{
	auto dataPoints = jsonReader_.GetKeyValueDataPoints();
	auto size = std::distance(dataPoints.find(startDate), dataPoints.find(endDate));
	std::vector<double> rangeVector(size);
	std::transform(dataPoints.find(startDate), dataPoints.find(endDate), rangeVector.begin(),
		[](decltype(dataPoints)::value_type& valueType) 
	{
		return valueType.second;
	});
	return rangeVector;
}

double Statistics::GetMeanDataPoint() const
{
	auto dataPoints = jsonReader_.GetDataPoints();
	
	auto total = std::accumulate(dataPoints.cbegin(), dataPoints.cend(), 0.0, 
		[](double prev, const decltype(dataPoints)::value_type& value)
	{
		return prev + value.second;
	});

	return total/dataPoints.size();
}

double Statistics::GetMedianDataPoint() const
{
	auto dataPoints = jsonReader_.GetDataPoints();
	size_t medianPoint = dataPoints.size() / 2;
	return dataPoints[medianPoint].second;
}

double Statistics::GetStandardDevDataPoint() const
{
	auto mean = GetMeanDataPoint();
	auto dataPoints = jsonReader_.GetDataPoints();

	double standardDeviation = 0.0;
	for (auto dataPoint: dataPoints)
		standardDeviation += std::pow(dataPoint.second - mean, 2);

	return std::sqrt(standardDeviation / dataPoints.size());
}