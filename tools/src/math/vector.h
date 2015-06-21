#pragma once

#include <ostream>

#include "complex.h"

namespace cppe {
	namespace math {

		template<typename T>
		class vector2 {
		public:
			vector2() = default;
			vector2(const T& x, const T& y) : x(x), y(y) {}
			~vector2() = default;

            const bool operator==(const vector2& vector) const {
                return ((this->x == vector.x) && (this->y == vector.y));
            }

            const bool operator!=(const vector2& vector) const {
                return !(*this == vector);
            }

            vector2& operator=(const vector2& vector) {
                if (*this != vector) {
                    x = vector.x;
                    y = vector.y;
                }

                return *this;
            }

			friend std::ostream& operator<<(std::ostream& stream, const vector2& vector) {
				stream << "vector2 contains: " << vector.x << ", " << vector.y;
				return stream;
			}

			friend vector2 operator+(vector2 left, const vector2& right) {
				left.x += right.x;
				left.y += right.y;
				return left;
			}
			friend vector2 operator-(vector2 left, const vector2& right) {
				left.x -= right.x;
				left.y -= right.y;
				return left;
			}
			friend vector2 operator*(vector2 left, const vector2& right) {
				left.x *= right.x;
				left.y *= right.y;
				return left;
			}
			friend vector2 operator/(vector2 left, const vector2& right) {
				left.x /= right.x;
				left.y /= right.y;
				return left;
			}

            friend vector2 operator+(vector2 left, const T& right) {
                left.x += right;
                left.y += right;
                return left;
            }
            friend vector2 operator-(vector2 left, const T& right) {
                left.x -= right;
                left.y -= right;
                return left;
            }
            friend vector2 operator*(vector2 left, const T& right) {
                left.x *= right;
                left.y *= right;
                return left;
            }
            friend vector2 operator/(vector2 left, const T& right) {
                left.x /= right;
                left.y /= right;
                return left;
            }

			vector2& operator+=(const vector2& vector);
			vector2& operator-=(const vector2& vector);
			vector2& operator*=(const vector2& vector);
			vector2& operator/=(const vector2& vector);

            vector2& operator+=(const T& value);
            vector2& operator-=(const T& value);
            vector2& operator*=(const T& value);
            vector2& operator/=(const T& value);

			const float magnitude() const;

			void scale(const float& scalar);
			const float dotProduct(const vector2& vector);
			const T crossProduct(const vector2& vector);
            const vector2 unit() const;

			T x, y;
		};

        typedef vector2<complexi> vector2ci;
        typedef vector2<complexf> vector2cf;
        typedef vector2<complexd> vector2cd;
        typedef vector2<double> vector2d;
		typedef vector2<float> vector2f;
		typedef vector2<int> vector2i;

		template<typename T>
		class vector3 {
		public:
			vector3() = default;
			vector3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}
            vector3(const vector2<T>& vector) : x(vector.x), y(vector.y), z(0) {}
			~vector3() = default;

            const bool operator==(const vector3& vector) const {
                return ((this->x == vector.x) && (this->y == vector.y) && (this->z == vector.z));
            }

            const bool operator!=(const vector3& vector) const {
                return !(*this == vector);
            }

            vector3& operator=(const vector3& vector) {
                if (*this != vector) {
                    x = vector.x;
                    y = vector.y;
                    z = vector.z;
                }

                return *this;
            }

			friend std::ostream& operator<<(std::ostream& stream, const vector3& vector) {
				stream << "vector3 contains: " << vector.x << ", " << vector.y << ", " << vector.z;
				return stream;
			}

			friend vector3 operator+(vector3 left, const vector3& right) {
				left.x += right.x;
				left.y += right.y;
				left.z += right.z;
				return left;
			}
			friend vector3 operator-(vector3 left, const vector3& right) {
				left.x -= right.x;
				left.y -= right.y;
				left.z -= right.z;
				return left;
			}
			friend vector3 operator*(vector3 left, const vector3& right) {
				left.x *= right.x;
				left.y *= right.y;
				left.z *= right.z;
				return left;
			}
			friend vector3 operator/(vector3 left, const vector3& right) {
				left.x /= right.x;
				left.y /= right.y;
				left.z /= right.z;
				return left;
			}

            friend vector3 operator+(vector3 left, const T& right) {
                left.x += right;
                left.y += right;
                left.z += right;
                return left;
            }
            friend vector3 operator-(vector3 left, const T& right) {
                left.x -= right;
                left.y -= right;
                left.z -= right;
                return left;
            }
            friend vector3 operator*(vector3 left, const T& right) {
                left.x *= right;
                left.y *= right;
                left.z *= right;
                return left;
            }
            friend vector3 operator/(vector3 left, const T& right) {
                left.x /= right;
                left.y /= right;
                left.z /= right;
                return left;
            }

			vector3& operator+=(const vector3& vector);
			vector3& operator-=(const vector3& vector);
			vector3& operator*=(const vector3& vector);
			vector3& operator/=(const vector3& vector);

            vector3& operator+=(const T& value);
            vector3& operator-=(const T& value);
            vector3& operator*=(const T& value);
            vector3& operator/=(const T& value);

			const float magnitude() const;

			void scale(const float& scalar);
			const float dotProduct(const vector3& vector);
			const vector3 crossProduct(const vector3& vector);
            const vector3 unit() const;

			T x, y, z;
		};

        
        typedef vector3<complexi> vector3ci;
        typedef vector3<complexf> vector3cf;
        typedef vector3<complexd> vector3cd;
        typedef vector3<double> vector3d;
		typedef vector3<float> vector3f;
		typedef vector3<int> vector3i;

		template<typename T>
		class vector4 {
		public:
			vector4() = default;
			vector4(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}
            vector4(const vector2<T>& vector) : x(vector.x), y(vector.y), z(0), w(0) {}
            vector4(const vector3<T>& vector) : x(vector.x), y(vector.y), z(vector.z), w(0) {}
			~vector4() = default;
           
            const bool operator==(const vector4& vector) const {
                return ((this->x == vector.x) && (this->y == vector.y) && (this->z == vector.z) && (this->w == vector.w));
            }

            const bool operator!=(const vector4& vector) const {
                return !(*this == vector);
            }

            vector4& operator=(const vector4& vector) {
                if (*this != vector) {
                    x = vector.x;
                    y = vector.y;
                    z = vector.z;
                    w = vector.w;
                }

                return *this;
            }

			friend std::ostream& operator<<(std::ostream& stream, const vector4& vector) {
				stream << "vector4 contains: " << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w;
				return stream;
			}

			friend vector4 operator+(vector4 left, const vector4& right) {
				left.x += right.x;
				left.y += right.y;
				left.z += right.z;
				left.w += right.w;
				return left;
			}
			friend vector4 operator-(vector4 left, const vector4& right) {
				left.x -= right.x;
				left.y -= right.y;
				left.z -= right.z;
				left.w -= right.w;
				return left;
			}
			friend vector4 operator*(vector4 left, const vector4& right) {
				left.x *= right.x;
				left.y *= right.y;
				left.z *= right.z;
				left.w *= right.w;
				return left;
			}
			friend vector4 operator/(vector4 left, const vector4& right) {
				left.x /= right.x;
				left.y /= right.y;
				left.z /= right.z;
				left.w /= right.w;
				return left;
			}

            friend vector4 operator+(vector4 left, const T& right) {
                left.x += right;
                left.y += right;
                left.z += right;
                left.w += right;
                return left;
            }
            friend vector4 operator-(vector4 left, const T& right) {
                left.x -= right;
                left.y -= right;
                left.z -= right;
                left.w -= right;
                return left;
            }
            friend vector4 operator*(vector4 left, const T& right) {
                left.x *= right;
                left.y *= right;
                left.z *= right;
                left.w *= right;
                return left;
            }
            friend vector4 operator/(vector4 left, const T& right) {
                left.x /= right;
                left.y /= right;
                left.z /= right;
                left.w /= right;
                return left;
            }

			vector4& operator+=(const vector4& vector);
			vector4& operator-=(const vector4& vector);
			vector4& operator*=(const vector4& vector);
			vector4& operator/=(const vector4& vector);

            vector4& operator+=(const T& value);
            vector4& operator-=(const T& value);
            vector4& operator*=(const T& value);
            vector4& operator/=(const T& value);

			const float magnitude() const;

			void scale(const float& scalar);
			const float dotProduct(const vector4& vector);
			const vector4 crossProduct(const vector4& vector);
            const vector4 unit() const;

			T x, y, z, w;
		};

        typedef vector4<complexi> vector4ci;
        typedef vector4<complexf> vector4cf;
        typedef vector4<complexd> vector4cd;
        typedef vector4<double> vector4d;
		typedef vector4<float> vector4f;
		typedef vector4<int> vector4i;
	}
}
