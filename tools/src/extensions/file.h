#pragma once

#include <string>
#include <memory>

#include <glew.h>

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

			static void print_current_working_directory();

		private:
			std::string file_name;
			std::string file_data;
		};
	}
}