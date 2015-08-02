#pragma once

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

            void write(const bool& is_binary = false) {
                assert(_file_name != "");

                char* format = "w";
                if (is_binary) {
                    format = STR_CONCATENATE("w", "b");
                }

                FILE* file = fopen(_file_name.c_str(), format);

                if (!file) {
                    console::output_line("ERROR: failed to open file...");
                    return;
                }

                fwrite(_file_buffer, sizeof(T), _size, file);

                fclose(file);
            }

            const long int find(const T& data) {
                int length = 0;
                if (std::is_same<T, char>::value) {
                    length = strlen(file_buffer);
                } else {
                    length = sizeof(file_buffer);
                }
                for (int i = 0; i < length; ++i) {
                    if (file_buffer[i] == data) {
                        return i;
                    }
                }
                return -1;
            }

            const void read_at(const unsigned long int& position, const bool& is_binary = false) {
                assert(_file_name != "" || !_file_name.empty());

                char* format = "r";
                if (is_binary) {
                    format = STR_CONCATENATE("r", "b");
                }

                FILE* file = fopen(_file_name.c_str(), format);

                if (!file) {
                    console::output_line("ERROR: failed to open file...");
                    return;
                }

                _file_buffer = new T();
                memset(_file_buffer, 0, 1);
                fseek(file, position * sizeof(T), SEEK_SET);

                fread(_file_buffer, sizeof(T), 1, file);
                fclose(file);
            }

            const void read(unsigned long int begin, unsigned long int end, const bool& is_binary = false) {
                assert(_file_name != "" || !_file_name.empty());

                char* format = "r";
                if (is_binary) {
                    format = STR_CONCATENATE("r", "b");
                }

                FILE* file = fopen(_file_name.c_str(), format);

                if (!file) {
                    console::output_line("ERROR: failed to open file...");
                    return;
                }

                fseek(file, 0, SEEK_END);
                unsigned long length = ftell(file) / sizeof(T);

                if (begin > length) {
                    begin -= length;
                }

                if (end == 0 || end > length || end < begin) {
                    end = length;
                }

                fseek(file, begin * sizeof(T), SEEK_SET);

                _size = end;

                if (std::is_same<char, T>::value) {
                    _size = end + 1;
                }

                _file_buffer = new T[_size];
                memset(_file_buffer, 0, _size);

                fread(_file_buffer, sizeof(T), end, file);
                fclose(file);
            }

            T* data_ptr() const {
                return (T*)_file_buffer;
            }

            T& data() const {
                return *((T*)_file_buffer);
            }

            void fill(const void* data, const unsigned long int size) {
                _size = size;

                _file_buffer = new T[_size];
                memset(_file_buffer, 0, _size);
                memcpy(_file_buffer, data, _size * sizeof(T));
            }

            void empty() {
                memset(_file_buffer, 0, _size);
            }

        private:
            std::string _file_name;
            void* _file_buffer;
            unsigned long int _size;
        };
    }
}
