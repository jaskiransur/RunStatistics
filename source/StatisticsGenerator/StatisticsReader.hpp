#ifndef statsgenerator_statisticsreaderimpl_hpp
#define statsgenerator_statisticsreaderimpl_hpp

#define TEMPLATE template<template<class> class T, class P>
#define SCOPE StatisticsReaderImpl<T, P, std::enable_if_t<std::is_same<T<P>, TreeReader<boost::property_tree::ptree>>::value>>

TEMPLATE
SCOPE::StatisticsReaderImpl(std::string&& _path)
	: treeReader_(T<P>(std::forward<std::string>(_path)))
{
}

TEMPLATE
SCOPE::StatisticsReaderImpl(T<P>&& _treeReader)
	: treeReader_(std::forward<T<P>>(_treeReader))
{
}


TEMPLATE
SCOPE::StatisticsReaderImpl(SCOPE&& _other) noexcept
	: treeReader_(std::move(_other.treeReader_))
{
}

TEMPLATE
SCOPE& SCOPE::operator=(SCOPE&& _other) noexcept
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);
	treeReader_ = std::move(_other.treeReader_);
	return *this;
}

TEMPLATE
std::vector<std::pair<std::string, double>> SCOPE::GetDataPoints()
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);
	return treeReader_.GetVector<double>("bpi");
}

TEMPLATE
std::map<std::string, double> SCOPE::GetKeyValueDataPoints()
{
	std::lock_guard<std::recursive_mutex> guard(mutex_);
	return treeReader_.GetKeyValues<double>(std::string("bpi"));
}

#undef SCOPE
#undef TEMPLATE
#endif // !statsgenerator_statisticsreaderimpl_hpp