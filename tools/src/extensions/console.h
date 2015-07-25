#pragma once

#include "color.h"

#include "file.h"

#include <string>
#include <iostream>

namespace cppe {
	namespace io {
		class console {
		public:
            static void output_current_directory() {
                output_line(file::current_working_directory());
            }

			static void set_color_scheme(const unsigned& background_color_code, const unsigned& foreground_color_code) {
#ifdef linux
				format = "";
				background_color = AS_BACKGROUND(color_code);
#else
				foreground_color = foreground_color_code;
				background_color = background_color_code;

				std::string color_scheme = "color ";
				char background = AS_ASCII(background_color_code);
				char foreground = AS_ASCII(foreground_color_code);

				color_scheme += background;
				color_scheme += foreground;

				system(color_scheme.c_str());
#endif
			}

			static void default() {
#ifdef linux
				format = "";
				foreground_color = white;
				background_color = purple;
#else
				foreground_color = WHITE;
				background_color = BLACK;

				std::string color_scheme = "color ";
				color_scheme += char(AS_ASCII(background_color));
				color_scheme += char(AS_ASCII(foreground_color));

				system(color_scheme.c_str());
#endif
			}

			template <typename T, typename... U>
			static void colored_output(const unsigned& color_code, const T& arg, const U&... args) {
#ifdef linux
				std::cout << "\033[" << color_code << "m";
#else
				HANDLE handle;
				handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, color_code | AS_BACKGROUND(background_color));
#endif
				std::cout << arg;
				if (sizeof...(args) == 0) {
					return;
				}
				colored_output(color_code, args...);
			}

			template <typename T, typename... U>
			static void colored_output_line(const unsigned& color_code, const T& arg, const U&... args) {
#ifdef linux
				std::cout << "\033[" << color_code << "m";
#else
				HANDLE handle;
				handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, color_code | AS_BACKGROUND(background_color));
#endif
				colored_output(color_code, arg, args...);
				std::cout << std::endl;
			}

			template <typename T, typename... U>
			static void output(const T& arg, const U&... args) {
				colored_output(foreground_color, arg, args...);
			}

            template <typename T>
            static void input(T& value) {
                std::cout << "> ";
                std::cin >> value;
            }

			template <typename T, typename... U>
			static void output_line(const T& arg, const U&... args) {
				colored_output_line(foreground_color, arg, args...);
			}

			static void output_line() {
				std::cout << std::endl;
			}

			template <typename T>
			static void colored_output(const unsigned& color_code, const T& arg) {
#ifdef linux
				std::cout << "\033[" << color_code << "m";
#else
				HANDLE handle;
				handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, color_code | AS_BACKGROUND(background_color));
#endif
				std::cout << arg;
			}

        private:
			char* format = "";
			static unsigned foreground_color;
			static unsigned background_color;
			unsigned attributes = 0;
		};
	}
}
