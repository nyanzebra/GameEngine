#ifndef CACHE_H
#define CACHE_H

#include <map>
#include <string>
#include <memory>

#include "file.h"

namespace cppe {
    namespace memory {
        struct memory_unit { 
            enum { value = 0 };
        };

        template<unsigned int Size = 1>
        struct byte : memory_unit {
            enum { value = Size };
        };

        template<unsigned int Size = 1>
        struct kilobyte : memory_unit {
            enum { value = 1024 * byte<Size - 1>::value; };
        };

        template<unsigned int Size = 1>
        struct megabyte :memory_unit {
            enum { value = 1024 * kilobyte<Size - 1>::value; };
        };

        template<unsigned int Size = 1>
        struct gigabyte :memory_unit {
            enum { value = 1024 * megabyte<Size - 1>::value; };
        };

        template<unsigned int Size = 1>
        struct terabyte :memory_unit {
            enum { value = 1024 * gigabyte<Size - 1>::value; };
        };

        template <class Capacity = kilobyte<1>,
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
            cache(const char* name) : _name(name) { _name += ".ftlasset"; };
            cache(const cache&) = default;
            ~cache() { store(); }

            void add(const Key& key, const std::shared_ptr<Value>& value) {
                if (_current_size < Capacity::value / sizeof(char)) {
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

            void remove(const Key& key);

            const bool is_shareable(const Key& key) {
                return !_cache[key].expired();
            }

            const Value&& operator[](const Key& key) {
                console::output("getting", key);
                auto sharedptr = _cache[key].lock();
                console::output(*sharedptr);
                return std::move(*sharedptr);
            }

            const Value&& get(const Key& key) {
                console::output("getting", key);
                auto sharedptr = _cache[key].lock();
                console::output(*sharedptr);
                return std::move(*sharedptr);
            }

            void clear();

            void store();

            void fill() {
                cppe::io::file<CachePairInstance> disk(_name);
                disk.read(FILE_ALL, true);                   
                for (int i = 0; i < Capacity::value / sizeof(Value) && i < sizeof(disk.data_ptr()) / sizeof(CachePairInstance); ++i) {
                    try {
                        if (disk.data_ptr()) {
                            auto it = disk.data_ptr()[i];

                            cppe::io::console::output_line(Capacity::value / sizeof(Value), sizeof(disk.data_ptr()) / sizeof(CachePairInstance));
                            cppe::io::console::output_line(sizeof(disk.data_ptr()));
                            cppe::io::console::output_line(sizeof(disk.data_ptr()[i]));
 
                            _cache.insert(std::pair<Key, std::weak_ptr<Value>>(it.first, std::make_shared<Value>(it.second)));
                            cppe::io::console::output_line(it.second);

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
    }
}

#include "cache.cpp"
#endif
