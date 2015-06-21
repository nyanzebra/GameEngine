#pragma once

namespace cppe {
	namespace pattern {
		namespace creational {
			template <typename T>
			class singleton {
			public:
				static T& instance() {
					static T singleton;

					return singleton;
				}
			private:
				singleton() = default;
				singleton(const singleton& singleton) = delete;
				singleton operator=(const singleton& singleton) = delete;
				~singleton() = default;
			};
		}
	}
}
