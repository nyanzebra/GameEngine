#pragma once

#include <functional>

namespace cppe {
	namespace pattern {
		namespace structural {
			template <typename Adaptee_T, typename... Adaptee_Args>
			class Adapter {
			public:
				Adapter(const std::function<Adaptee_T(Adaptee_Args...)> function_to_call) : 
					adaptee_function(function_to_call) {}

				template <typename... Args>
				void adapt(const Args... adapted_parameters, 
						   const std::function<std::tuple<Adaptee_Args...>(Args...)> conversion_function) {
					adaptee_function(conversion_function(adapted_parameters));
				}


			private:
				std::function<Adaptee_T(Adaptee_Args...)>  adaptee_function;
			};
		}
	}
}
