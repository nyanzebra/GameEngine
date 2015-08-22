#ifdef CACHE_H
                          
namespace cppe {
    namespace memory {
        template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::add(const Key& key, const Value& value) {
            if (_current_size < Capacity / sizeof(char)) {
                _current_size += sizeof(Value);
                console::output(_current_size);
                if (_cache.find(key) == _cache.end()) {
                    _cache[key] = value;
                    _cache_ref[key] = value;
                }
            } else {
                store();
            }
        }

        template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::remove(const Key& key) {
            _cache.erase(key);
        }

        template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        const Value&& cache<Capacity, Key, Value, Container, Comparator, Allocator>::operator[](const Key& key) {
            auto sharedptr = _cache[key].lock();
            return std::move(*sharedptr);
        }

        template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::clear() {
            _cache.clear();
        }

        template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::store() {
            cppe::io::file<Value> disk(_name);

            std::pair<Key,Value>* values = new std::pair<Key,Value>[_cache.size()];
            int i = 0;
            for (auto it = _cache.begin(); it != _cache.end(); ++it) {
                if (!it->second.expired()) {
                    values[i++] = std::pair<Key,Value>(it->first, *it->second.lock().get());  
                }
            }
            disk.fill(values, Capacity * sizeof(char));
            disk.write(true);
            clear();
        }

        template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
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


#endif
