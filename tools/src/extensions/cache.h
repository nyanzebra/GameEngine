#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <memory>
#include <vector>

#include "file.h"

namespace cppe {
namespace memory {

template< typename Value>
class cache_element {
public:
	cache_element() = default;
	cache_element(const Value& value) : _value(value) {}
	~cache_element() { if (std::is_pointer<Value>::value) { delete &_value; } }

	const bool& is_empty() { return _is_empty; }
	void is_empty(const bool& value) { _is_empty = value; }

	const size_t& hits() { return _hits; }
	void hits(const size_t& value) { _hits = value; }

	Value& value() { return _value; }
	void value(const Value& value) { _value = value; }

	void hit() { _hits++; }
private:
	bool _is_empty = false;
	size_t _hits = 0;
	Value _value;
};

template<typename Key, typename Value>
class cache_policy_base {
public:
	typedef Key key;
	typedef Value value;
protected:
	cache_policy_base() {}
	virtual ~cache_policy_base() { _cache.clear(); }

	virtual const bool add(const Key& key, const Value& value) = 0;

	virtual const bool remove(const Key& key) = 0;

	virtual Value& get(const Key& key) = 0;

	virtual const bool set(const Key& key, const Value& value) = 0;

	virtual const bool has(const Key& key) = 0;

	virtual Value& operator[](const Key& key) = 0;

	virtual void handle_miss(const Key& key) = 0;

	virtual const bool swap(const Key& key_first, const Key& key_second) = 0;

	virtual void kick() = 0;

	void clear() { _cache.clear(); }

	const unsigned int& size() const { return _current_size; }

	std::unordered_map<Key, cache_element<Value>, std::hash<Key>, std::equal_to<Key>, std::allocator<std::pair<const Key, Value>>> _cache;

	size_t _current_size = 0;
};

template<typename Key, typename Value, const size_t Capacity>
class cache_policy : public cache_policy_base<Key, Value> {
protected:
	cache_policy() { _cache.reserve(Capacity); }
	~cache_policy() = default;

	const bool add(const Key& key, const Value& value) {
		if (_current_size < Capacity) {
			_current_size += sizeof(Value);
			return try_add(key, value);
		} else {
			kick();
			_current_size += sizeof(Value);
			return try_add(key, value);
		}
	}

	const bool remove(const Key& key) {
		if (_cache.find(key) != _cache.end()) {
			_current_size -= sizeof(Value);
			_cache.erase(key);
			return true;
		}
		return false;
	}

	Value& get(const Key& key) {
		if (has(key)) {
			_cache[key].hit();
		} else {
			handle_miss(key);
		}

		return _cache[key].value();
	}

	const bool set(const Key& key, const Value& value) {
		if (_cache.find(key) != _cache.end()) {
			_cache[key] = cache_element<Value>(value);
			_cache[key].is_empty(false);
			return true;
		}
		return false;
	}

	const bool has(const Key& key) {
		if (_cache.find(key) != _cache.end()) {
			return true;
		}
		return false;
	}

	void handle_miss(const Key& key) {
		_cache[key] = cache_element<Value>();
		_cache[key].is_empty(true);
	}

	const bool swap(const Key& key_first, const Key& key_second) {
		if (has(key_first) && has(key_second)) {
			cache_element<Value> second_item = _cache[key_second];
			_cache[key_second] = _cache[key_first];
			_cache[key_first] = second_item;
			return true;
		}
		return false;
	}

	Value& operator[](const Key& key) {
		return get(key);
	}

	void kick() {
		auto lowest_hit = _cache.begin();
		for (auto it = _cache.begin(); it != _cache.end(); ++it) {
			lowest_hit = (it->second.hits() <= lowest_hit->second.hits()) ? it : lowest_hit;
		}
		remove(lowest_hit->first);
	}

private:
	inline const bool try_add(const Key& key, const Value& value) {
		if (_cache.find(key) == _cache.end()) {
			_cache[key] = cache_element<Value>(value);
			return true;
		}
		return false;
	}
};

template<class Policy, class = std::enable_if<std::is_base_of< Policy, cache_policy_base<typename Policy::key, typename Policy::value>>::value>>
class cache : private Policy {
private:
	using Policy::key;
	using Policy::add;
	using Policy::remove;
	using Policy::get;
	using Policy::set;
	using Policy::has;
	using Policy::handle_miss;
	using Policy::operator[];
	using Policy::swap;
	using Policy::size;
	using Policy::clear;
public:					 
	cache() = default;
	cache(const cache&) = default;
	~cache() = default;

	const bool add(const typename Policy::key& key, const typename Policy::value& value) {
		return Policy::add(key, value);
	}

	const bool remove(const typename Policy::key& key) {
		return Policy::remove(key);
	}

	typename Policy::value& operator[](const typename Policy::key& key) {
		return Policy::operator[](key);
	}

	typename Policy::value& get(const typename Policy::key& key) {
		return Policy::get(key);
	}

	const bool has(const typename Policy::key& key) {
		return Policy::has(key);
	}

	const bool set(const typename Policy::key& key) {
		return Policy::set(key);
	}

	const bool swap(const typename Policy::key& key_first, const typename Policy::key& key_second) {
		return Policy::swap(key_first, key_second);
	}

	void clear() { Policy::clear(); }

	const unsigned int& size() const { return Policy::size(); }
};

} // namespace memory
} // namespace cppe
