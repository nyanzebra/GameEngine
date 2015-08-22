#ifdef CACHE_H
                          
namespace cppe {
    namespace memory {
        /*template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::add(const Key& key, const Value& value) {
            if (_current_size < Capacity::value / sizeof(char)) {
                _current_size += sizeof(Value);
                if (_cache.find(key)!=_cache.end()) {
                    _cache[key] = std::make_shared<Value>(new Value(value));
                }
            } else {
                store();
            }
        }*/

        template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::remove(const Key& key) {
            _cache.erase(key);
        }

        /*template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        const Value&& cache<Capacity, Key, Value, Container, Comparator, Allocator>::operator[](const Key& key) {
            if(_cache[key].expired()) {
                return NULL;
            }

            return std::move(*(_cache[key].lock().get()));
        }*/

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
            disk.fill(values, Capacity::value * sizeof(char));
            disk.write(true);
            clear();
        }

        /*template <class Capacity = kilobyte<1>, typename Key = int, typename Value = int, template<class, class, class, class> class Container = std::map, typename Comparator = std::less<Value>, typename Allocator = std::allocator<Value>>
        void cache<Capacity, Key, Value, Container, Comparator, Allocator>::fill() {
            cppe::io::file<Cache::iterator> disk(_name);
            disk.read(FILE_ALL, true);
            for (int i = 0; i < Capacity::value; ++i) {
                if(disk.data_ptr()) {                                                      
                    _cache.insert(std::pair<Key,Value>(disk.data_ptr()[i].first,disk.data_ptr()[i].second))  ;
                }
            }
        }*/
    }
}


#endif
