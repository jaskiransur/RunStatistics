#include <boost/format.hpp>
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
#include "Statistics.h"
#include "StatisticsReader.h"

using statsgenerator::Statistics;

Statistics::Statistics(boost::filesystem::path path)
	:jsonReader_(std::move(path))
{

}

Statistics::Statistics(boost::filesystem::path path, const std::string& startDate, const std::string& endDate)
	: jsonReader_(std::move(path))
	, startDate_(startDate)
	, endDate_(endDate)
{

}

std::pair<std::string, double> Statistics::GetHighest()
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);
	auto dataPoints = GetDataPoints();
	
	auto it = std::max_element(dataPoints.cbegin(), dataPoints.cend(),
		[](const decltype(dataPoints)::value_type& leftPair, const decltype(dataPoints)::value_type& rightPair)
	{
		return leftPair.second < rightPair.second;
	});
	return *it;
}

std::pair<std::string, double> Statistics::GetLowest() 
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);

	auto dataPoints = GetDataPoints();

	auto it = std::min_element(dataPoints.cbegin(), dataPoints.cend(),
		[](const decltype(dataPoints)::value_type& leftPair, const decltype(dataPoints)::value_type& rightPair)
	{
		return leftPair.second < rightPair.second;
	});
	return *it;
}

std::vector<std::pair<std::string, double>> Statistics::GetDataPoints() 
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);

	return (!startDate_.empty() && !endDate_.empty())
		? GetDataPoints(startDate_, endDate_)
		: jsonReader_.GetDataPoints();
}

std::vector<std::pair<std::string, double>> Statistics::GetDataPoints(const std::string & startDate, const std::string & endDate)
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);

	auto dataPoints = jsonReader_.GetKeyValueDataPoints();
	if (dataPoints.find(startDate) == dataPoints.end())
		throw std::invalid_argument((boost::format("StartDate %1% is invalid") % startDate).str());

	if (dataPoints.find(endDate) == dataPoints.end())
		throw std::invalid_argument((boost::format("EndDate %1% is invalid") % endDate).str());

	auto lower_bound = dataPoints.lower_bound(startDate);
	auto upper_bound = dataPoints.upper_bound(endDate);
	
	const auto startDistanceFromBegin = std::distance(dataPoints.begin(), lower_bound);
	const auto endDistanceFromBegin = std::distance(dataPoints.begin(), upper_bound);

	if (startDistanceFromBegin > endDistanceFromBegin)
		throw std::runtime_error((boost::format("StartDate %1% is higher than end date %2%") % lower_bound->second %upper_bound->second).str());

	const auto size = endDistanceFromBegin - startDistanceFromBegin;

	std::vector<std::pair<std::string, double>> rangeVector(size);
	std::transform(lower_bound, upper_bound, rangeVector.begin(),
		[](decltype(dataPoints)::value_type& valueType) 
	{
		return std::make_pair(valueType.first, valueType.second);
	});
	return rangeVector;
}

namespace
{
	double GetSum(const std::vector<std::pair<std::string, double>>& dataPoints)
	{
		auto total = std::accumulate(dataPoints.cbegin(), dataPoints.cend(), 0.0,
			[](double prev, const std::decay_t<decltype(dataPoints)>::value_type& value)
		{
			return prev + value.second;
		});
		return total;
	}
}
double Statistics::GetMeanDataPoint() 
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);

	auto dataPoints = GetDataPoints();

	
	return GetSum(dataPoints)/dataPoints.size();
}

double Statistics::GetMedianDataPoint() 
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);

	auto dataPoints = GetDataPoints();

	size_t medianPoint = dataPoints.size() / 2;
	return dataPoints[medianPoint].second;
}

double Statistics::GetStandardDevDataPoint() 
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);

	auto dataPoints = GetDataPoints();
		
	auto mean = GetSum(dataPoints)/dataPoints.size();
	
	double standardDeviation = 0.0;
	for (auto dataPoint: dataPoints)
		standardDeviation += std::pow(dataPoint.second - mean, 2);

	return std::sqrt(standardDeviation / dataPoints.size());
}