#pragma once

#include <string>
#include <memory>

#include <GL/glew.h>

#ifdef _WIN32
#include <direct.h>
#ifndef CWD
#define CWD _getcwd
#endif
#else
#include <unistd.h>
#ifndef CWD
#define CWD getcwd
#endif
#endif

namespace cppe {
    namespace io {
        class file {
        public:
            file(const std::string& file_name) : file_name(file_name) {}
            file(const char* file_name) : file_name(file_name) {}
            ~file() = default;

            void write(const std::string& data);

            void append(const std::string& data);

            const std::string& read();

            const std::string& data() const;

            static std::string current_working_directory() {
                char path[FILENAME_MAX];
                CWD(path, sizeof(path));
                path[sizeof(path) - 1] = NULL;
                return path;
            }

        private:
            std::string file_name;
            std::string file_data;
        };
    }
}
