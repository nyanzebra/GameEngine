#pragma once

namespace cppe {
	namespace math {

		const float to_radians(const float& degrees);
        
        template <typename T>
        const T to_square(const T& value) { return value * value; }

        template <typename T>
        const bool within_range(const T& lower_bound, const T& value, const T& upper_bound) { return (lower_bound <= value && value <= upper_bound); }
	}
}
