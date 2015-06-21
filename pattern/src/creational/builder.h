#pragma once 

namespace cppe {
	namespace pattern {
		namespace creational {
			struct Build_Object {};

			class builder {
			public:
				builder() = default;
				virtual ~builder() = default;

			protected:
				virtual void build_structs(const Build_Object* T_params...) {}

				virtual void build_voids(const void* void_params...) {}

				virtual void build_strings(const char* string_params...) {}
				virtual void build_chars(const char char_params...) {}

				virtual void build_shorts(const short short_params...) {}
				virtual void build_ints(const int int_params...) {}
				virtual void build_longs(const long long_params...) {}
				virtual void build_doubles(const double double_params...) {}
				virtual void build_floats(const float float_params...) {}
				virtual void build_unsigneds(const unsigned unsigned_params...) {}

				virtual void build(void) {}

				virtual void build_struct(const Build_Object* T_param) {}
				virtual void build_void(const void* void_param) {}

				virtual void build_string(const char* string_param) {}
				virtual void build_char(const char char_param) {}

				virtual void build_short(const short short_param) {}
				virtual void build_int(const int int_param) {}
				virtual void build_long(const long long_param) {}
				virtual void build_double(const double double_param) {}
				virtual void build_float(const float float_param) {}
				virtual void build_unsigned(const unsigned unsigned_param) {}
			};
		}
	}
}
