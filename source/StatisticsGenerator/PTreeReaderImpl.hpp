#ifndef statsgenerator_ptreereaderimpl_hpp
#define statsgenerator_ptreereaderimpl_hpp

#include <vector>
#include <map>
#include <utility>
#include <string>
#include <memory>
#include <mutex>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

using namespace std;

namespace statsgenerator
{
	template<>
	class TreeReader<boost::property_tree::ptree>
	{
	public:
		using value_type = boost::property_tree::ptree;

		TreeReader(boost::filesystem::path&& path)
		:path_(std::move(path))
		{
		}

		TreeReader(const boost::filesystem::path& path)
			:path_(path)
		{
		}

		TreeReader(const TreeReader& other)
			: path_(other.path_)
			, tree_(other.tree_)
		{
		}
		
		TreeReader& operator=(const TreeReader& other)
		{
			std::lock_guard<std::recursive_mutex> guard(mutex_);
			auto copy = TreeReader(other);
			std::swap(path_, copy.path_);
			std::swap(tree_, copy.tree_);
			return *this;
		}

		TreeReader(TreeReader&& other)
			: path_(std::move(other.path_))
			, tree_(std::move(other.tree_))
		{
		}

		TreeReader& operator=(TreeReader&& other)
		{
			std::lock_guard<std::recursive_mutex> guard(mutex_);

			path_ = std::move(other.path_);
			tree_ = std::move(other.tree_);
			return *this;
		}

		~TreeReader() = default;

		template<typename U>
		U GetScaler(std::string && key)
		{
			std::lock_guard<std::recursive_mutex> guard(mutex_);

			auto childTree = Ptree().get_child_optional(key);
			if (childTree)
			{
				auto& valueOptional = childTree->get_value_optional<U>();
				if (valueOptional)
					return valueOptional.value();
				throw std::runtime_error("requested key has no associated values");
				
			}
			throw std::runtime_error("requested key not found");
		}

		template<typename U>
		::std::vector<std::pair<std::string, U>> GetVector(const std::string & key) 
		{
			std::lock_guard<std::recursive_mutex> guard(mutex_);

			auto childTree = Ptree().get_child_optional(key);
			if (childTree)
			{
				std::vector<std::pair<std::string, U>> container;
				for (auto& keyValuePair : childTree.get())
				{
					container.emplace_back(keyValuePair.first, keyValuePair.second.get_value<U>());
				}
				return container;
			}
			
			throw std::runtime_error("Key not found");
		};

		template<typename U>
		::std::map<std::string, U> GetKeyValues(const std::string& key)
		{
			std::lock_guard<std::recursive_mutex> guard(mutex_);
			auto childTree = Ptree().get_child_optional(key);
			if (childTree)
			{
				std::map<std::string, U> container;
				for (auto& keyValuePair : childTree.get())
				{
					container[keyValuePair.first]= keyValuePair.second.get_value<U>();
				}
				return container;
			}

			throw std::runtime_error("Key not found");
		};
	private:
		boost::property_tree::ptree& Ptree()
		{
			if (tree_.empty())
			{
				if (!boost::filesystem::exists(path_))
					throw std::runtime_error(boost::str(boost::format("Invalid path to a json file %1%") % path_.string()));
				boost::property_tree::read_json(path_.string(), tree_);
			}
			return tree_;
		}
		boost::filesystem::path path_;
		boost::property_tree::ptree tree_;
		std::recursive_mutex mutex_;
	};
}
#endif // !statsgenerator_ptreereaderimpl_hpp