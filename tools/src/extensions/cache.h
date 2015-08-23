#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

#include "file.h"

namespace cppe {
namespace memory {

constexpr unsigned long long int operator"" _byte(unsigned long long int size) { return size; }
constexpr unsigned long long int operator"" _kilobyte(unsigned long long int size) { return size * 1024_byte; }
constexpr unsigned long long int operator"" _megabyte(unsigned long long int size) { return size * 1024_kilobyte; }
constexpr unsigned long long int operator"" _gigabyte(unsigned long long int size) { return size * 1024_megabyte; }
constexpr unsigned long long int operator"" _terabyte(unsigned long long int size) { return size * 1024_gigabyte; }
constexpr unsigned long long int operator"" _petabyte(unsigned long long int size) { return size * 1024_terabyte; }

template <typename Key, typename Value,
	size_t Capacity = 1_kilobyte,
	template<class, class, class, class> class Container = std::map,
	typename Comparator = std::less<Value>,
	typename Allocator = std::allocator < Value >>
class cache {
	typedef Container<const Key, std::weak_ptr<Value>, Comparator, Allocator> WeakCache;
	typedef Container<const Key, std::shared_ptr<Value>, Comparator, Allocator> StrongCache;
	typedef std::pair<Key, Value> CachePairInstance;
public:
	cache(const char* name) : _name(name) {};
	cache(const cache&) = default;
	~cache() = default;

	void add(const Key& key, const std::shared_ptr<Value>& value) {
		if (_current_size < Capacity / sizeof(char)) {
			_current_size += sizeof(Value);
			if (_cache.find(key) == _cache.end()) {
				_cache[key] = value;
				_cache_ref[key] = value;
			}
		} else {
			store();
		}
	}

	void remove(const Key& key) { _cache.erase(key); }

	const bool is_shareable(const Key& key) { return !_cache[key].expired(); }

	const Value& operator[](const Key& key) {
		if (auto shp = _cache[key].lock()) {
			return *shp;
		}
		return NULL;
	}

	void clear() { _cache.clear(); _cache_ref.clear(); }

	void store() {
		cppe::io::file<Value> disk(_name);

		std::vector<std::pair<Key, Value>> values;
		for (auto it = _cache.begin(); it != _cache.end(); ++it) {
			if (!it->second.expired()) {
				values.push_back(std::pair<Key, Value>(it->first, *it->second.lock()));
			}
		}
		disk.fill(values.data(), Capacity * sizeof(char));
		disk.write(true);
		clear();
	}

	void fill() {
		cppe::io::file<CachePairInstance> disk(_name);
		disk.read(FILE_ALL, true);
		for (int i = 0; i < Capacity / sizeof(Value) && i < sizeof(disk.data_ptr()) / sizeof(CachePairInstance); ++i) {
			try {
				if (disk.data_ptr()) {
					auto it = disk.data_ptr()[i];
					auto shp = std::make_shared<Value>(it.second);
					_cache[it.first] = shp;
					_cache_ref[it.first] = shp;
				}
			} catch (std::exception e) {
				console::output_line(e.what());
			}
		}
	}

	const unsigned int& size() const { return _current_size; }

private:
	std::string _name;
	WeakCache _cache;
	StrongCache _cache_ref;
	unsigned int _current_size = 0;
};

} // namespace memory
} // namespace cppe
