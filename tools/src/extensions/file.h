#ifndef FILE_H
#define FILE_H

#include <string>
#include <memory>

#include <GL/glew.h>

#include "console.h"

#include <assert.h>
#include <stdio.h>
#include <FreeImage.h>

namespace cppe {
    namespace io {

#ifndef CONCATENATE
#define CONCATENATE(a,b) a ## b
#define EXPAND_CONCATENATE(a,b) CONCATENATE(a,b)
#define STR_CONCATENATE(a,b) a b
#endif

#define FILE_START  0
#define FILE_FINISH  -1
#define FILE_ALL FILE_START, FILE_FINISH

        template<typename T = char>
        class file {
        public:
            file(const std::string& file_name) : _file_name(file_name) {}
            file(const char* file_name) : _file_name(file_name) {}
            ~file() { delete _file_buffer; }

            void write(const bool& is_binary = false);

            const long int find(const T& data);

            const void read_at(const unsigned long int& position, const bool& is_binary = false);

            const void read(unsigned long int begin, unsigned long int end, const bool& is_binary = false);

            T* data_ptr() const;

            T& data() const;

            void fill(const void* data, const unsigned long int size);

            void empty();

        private:
            std::string _file_name;
            void* _file_buffer;
            unsigned long int _size;
        };
    }
}

#include "file.cpp"
#endif
