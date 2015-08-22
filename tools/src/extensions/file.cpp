#ifdef FILE_H

namespace cppe {
    namespace io{

        template<typename T>
        void file<T>::write(const bool& is_binary) {
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
        template<typename T>
        const long int file<T>::find(const T& data) {
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
        template<typename T>
        const void file<T>::read_at(const unsigned long int& position, const bool& is_binary) {
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
        template<typename T>
        const void file<T>::read(unsigned long int begin, unsigned long int end, const bool& is_binary) {
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
        template<typename T>
        T* file<T>::data_ptr() const {
            return (T*)_file_buffer;
        }
        template<typename T>
        T& file<T>::data() const {
            return *((T*)_file_buffer);
        }
        template<typename T>
        void file<T>::fill(const void* data, const unsigned long int size) {
            _size = size;

            _file_buffer = new T[_size];
            memset(_file_buffer, 0, _size);
            memcpy(_file_buffer, data, _size * sizeof(T));
        }
        template<typename T>
        void file<T>::empty() {
            memset(_file_buffer, 0, _size);
        }
}
}
#endif
