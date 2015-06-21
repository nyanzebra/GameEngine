#pragma once

#include <string>
#include <sstream>
#include <iomanip>

namespace cppe {
	namespace string {
		template <typename T>
		std::string to_string_with_precision(const T a_value, const int n = 6) {
			std::ostringstream out;
			out << std::setprecision(n) << a_value;
			return out.str();
		}

		inline char* as_char_array(const std::string& str) {
			char* a = new char[str.size() + 1];
			a[str.size()] = 0;
			std::memcpy(a, str.c_str(), str.size());
			return a;
		}
	}
}
