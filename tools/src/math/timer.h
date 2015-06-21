#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace cppe {
	namespace math {
		class Timer {
		public:
			Timer() {
#ifdef _WIN32
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				this->frequency = 1.0 / frequency.QuadPart;
				QueryPerformanceCounter(&start_time);
#else
				long long int frequency;
#endif
			}
			void reset() {
				QueryPerformanceCounter(&start_time);
			}

			float time() {
#ifdef _WIN32
				LARGE_INTEGER current_time;
				QueryPerformanceCounter(&current_time);
				return (float)((current_time.QuadPart - start_time.QuadPart) * frequency);
#else
				long long int current_time;
#endif		
			}
		private:
			double frequency;
#ifdef _WIN32
			LARGE_INTEGER start_time;
#else
			long long int start_time;
#endif
		};
	}
}