#pragma once

#include <map>
#include <string>
#include <memory>

#include "file.h"

namespace cppe {
    namespace memory {
        template <size_t Count> struct byte : public std::integral_constant<size_t, Count> {};
        template <size_t Count> struct kilobyte : public std::integral_constant<size_t, byte<1024> * Count> {};
        template <size_t Count> struct megabyte : public std::integral_constant<size_t, kilobyte<1024> * Count> {};
        template <size_t Count> struct gigabyte : public std::integral_constant<size_t, megabyte<1024> * Count> {};
        template <size_t Count> struct terabyte : public std::integral_constant<size_t, terabyte<1024> * Count> {};  

        template <size_t Capacity = kilobyte<1>::value,
            typename Key = int,
            typename Value = int,
            template<class, class, class, class> class Container = std::map,
            typename Comparator = std::less<Value>,
            typename Allocator = std::allocator < Value >>
        class cache {
            typedef Container<const Key, std::weak_ptr<Value>, Comparator, Allocator> WeakCache;
            typedef Container<const Key, std::shared_ptr<Value>, Comparator, Allocator> StrongCache;
            typedef std::pair<Key, Value> CachePairInstance;
        public:
            cache(const char* name) : _name(std::string(name) + ".ftlasset") {};
            cache(const cache&) = default;
            ~cache() { store(); }

            void add(const Key& key, const std::shared_ptr<Value>& value);

            void remove(const Key& key);

            const bool is_shareable(const Key& key) {
                return !_cache[key].expired();
            }

            const Value&& operator[](const Key& key);

            void clear();

            void store();

            void fill();

            const unsigned int& size() const { return _current_size; }

        private:
            std::string _name;
            WeakCache _cache;
            StrongCache _cache_ref;
            unsigned int _current_size = 0;
        };

        template <class Capacity = kilobyte<1>::value, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::add(const Key& key, const Value& value) {
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

        template <class Capacity = kilobyte<1>::value, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::remove(const Key& key) {
            _cache.erase(key);
        }

        template <class Capacity = kilobyte<1>::value, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        const Value&& cache<Capacity, Key, Value, Container, Comparator, Allocator>::operator[](const Key& key) {
            auto sharedptr = _cache[key].lock();
            return std::move(*sharedptr);
        }

        template <class Capacity = kilobyte<1>::value, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::clear() {
            _cache.clear();
        }

        template <class Capacity = kilobyte<1>::value, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::store() {
            cppe::io::file<Value> disk(_name);

            std::pair<Key, Value>* values = new std::pair<Key, Value>[_cache.size()];
            int i = 0;
            for (auto it = _cache.begin(); it != _cache.end(); ++it) {
                if (!it->second.expired()) {
                    values[i++] = std::pair<Key, Value>(it->first, *it->second.lock().get());
                }
            }
            disk.fill(values, Capacity * sizeof(char));
            disk.write(true);
            clear();
        }

        template <class Capacity = kilobyte<1>::value, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::fill() {
            cppe::io::file<CachePairInstance> disk(_name);
            disk.read(FILE_ALL, true);
            for (int i = 0; i < Capacity / sizeof(Value) && i < sizeof(disk.data_ptr()) / sizeof(CachePairInstance); ++i) {
                try {
                    if (disk.data_ptr()) {
                        auto it = disk.data_ptr()[i];

                        _cache.insert(std::pair<Key, std::weak_ptr<Value>>(it.first, std::make_shared<Value>(it.second)));
                    }
                } catch (std::exception e) {
                    console::output_line(e.what());
                }
            }
        }
    }
}
