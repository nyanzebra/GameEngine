#pragma once

#include <map>
#include <string>
#include <memory>
                      
#include "file.h"

namespace cppe {
    namespace memory {
        struct memory_unit {};

        template<unsigned int Size = 1>
        struct byte : memory_unit {
            enum { value = 1 + Byte<Size - 1>::value; };
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

        template <template Key = int, template Value = int, template<typename,typename> Container = std::map<Key,Value>, unsigned int Capacity = kilobyte<1>, typename Allocator = std::allocator>
        class cache {
        public:
            cache() { _cache = new Container<Key, std::unique_ptr<Value>, Allocator>; };
            cache(const cache&) = default;
            ~cache() = default;

            void add(const Key& key, const Value& value) {
                if (_current_size < Capacity) {
                    _current_size += sizeof(Value);
                    if (_cache[key].second) {
                        _cache[key].first++;
                        _cache[key].second = std::move(value);
                    }
                } else {
                    swap();
                }
            }

            void remove(const Key& key) {
                _cache.erase(key);
            }

            const Value& operator[](const Key& key) {
                _cache[key].first++;
                return _cache[key];
            }

            void clear() {
                _cache.clear();
            }

            void store() {
                cppe::io::file disk("retainer");
                for (auto it = _cache.begin(); it != _cache.end(); ++it) {
                    disk.append(it);
                }
            }
            void fill();

        private:
            std::string _name;
            Container<Key, std::unique_ptr<Value>> _cache;
            unsigned int _current_size = 0;
        };
    }
}
