#pragma once

#include <memory>

namespace cppe {
	namespace pattern {
		namespace creational {
			template <typename Base>
			class factory {
			public:
				factory() = default;
				factory(factory&& factory) = delete;
				~factory() = default;

				factory operator=(factory&& factory) = delete;

				template <typename Derived, typename... Args>
				static std::unique_ptr<Base> create(const Args&... args) {

					static_assert(std::is_base_of<Base, Derived>::value, "Derived class must inherit from Base class");

					static_assert(std::is_constructible<Derived, Args...>::value, "Must supply the correct arguments to Derived class");

					return std::unique_ptr<Derived>(new Derived(args...));
				}
			};
		}
	}
}
