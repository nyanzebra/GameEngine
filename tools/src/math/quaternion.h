#pragma once

#include "vector.h"
#include "matrix.h"
#include "complex.h"

#include <math.h>

namespace cppe {
    namespace math {
#define UNIT_TOLERANCE 0.3

        template <typename T = float>
        class quaternion {
        public:
            quaternion() = default;
            quaternion(const T& x, const T& y, const T& z, const T& real) : imaginary(x, y, z), real(real) {}
            quaternion(const complex<T>& x, const complex<T>& y, const complex<T>& z, const T& real) : imaginary(x, y, z), real(real) {}
            quaternion(const complex<T>& x, const complex<T>& y, const complex<T>& z, const complex<T>& r) : imaginary(x, y, z), real(r.real) {}
            quaternion(const vector3<T>& imaginary, const T& real) : imaginary(imaginary), real(real) {}
            quaternion(const vector3<complex<T>>& imaginary, const T& real) : imaginary(imaginary), real(real) {}
            quaternion(const vector4<T>& quat) : imaginary(quat.x, quat.y, quat.z), real(quat.w) {}
            quaternion(const T& theta_x, const T& theta_y, const T& theta_z) {
                T cos_x = cos(theta_x / 2);
                T cos_y = cos(theta_y / 2);
                T cos_z = cos(theta_z / 2);

                T sin_x = sin(theta_x / 2);
                T sin_y = sin(theta_y / 2);
                T sin_z = sin(theta_z / 2);

                real = cos_z * cos_y * cos_x + sin_z * sin_y * sin_x;
                imaginary.x = cos_z * cos_y * sin_x + sin_z * sin_y * cos_x;
                imaginary.y = cos_z * sin_y * cos_x + sin_z * cos_y * sin_x;
                imaginary.z = sin_z * cos_y * cos_x + cos_z * sin_y * sin_x;
            }
            quaternion(const vector3<T>& euler) { quaternion(euler.x, euler.y, euler.z); }
            ~quaternion() = default;

            friend std::ostream& operator<<(std::ostream& stream, const quaternion& q) {
                stream << "quaternion contains: " << q.real << ", " << q.imaginary.x << ", " << q.imaginary.y << ", " << q.imaginary.z;
                return stream;
            }

            static quaternion identity() {
                return quaternion(0, 0, 0, 1);
            }

            const quaternion to_euler() const {

            }

            const T magnitude() const {
                return sqrt(norm());
            }

            const quaternion unit() const {
                return *this / magnitude();
            }

            const quaternion conjugate() const {
                return quaternion(0 - imaginary.x, 0 - imaginary.y, 0 - imaginary.z, +real);
            }

            const quaternion inverse() const {
                return conjugate().scale(1 / norm());
            }

            const quaternion scale(const T& scalar) const {
                return quaternion(imaginary.x * scalar, imaginary.y * scalar, imaginary.z * scalar, real * scalar);
            }

            const T norm() const {
                return (imaginary.x.square() + imaginary.y.square() + imaginary.z.square() + real * real);
            }

            const matrix4<T> as_matrix() const;

            const quaternion rotation(const T& angle) const;

            const bool operator==(const quaternion& q) const {
                return imaginary.x == q.imaginary.x && imaginary.y == q.imaginary.y && imaginary.z == q.imaginary.z && real == q.real;
            }

            const bool operator!=(const quaternion& q) const {
                return !(*this == q)
            }

            void operator=(const quaternion& q) {
                imaginary = q.imaginary;
                real = q.real;
            }

            friend const quaternion operator+(const quaternion& a, const quaternion& b) {
                return quaternion(a.imaginary + b.imaginary, a.real + b.real);
            }

            friend const quaternion operator-(const quaternion& a, const quaternion& b) {
                return quaternion(a.imaginary - b.imaginary, a.real - b.real);
            }

            friend const quaternion operator*(const quaternion& a, const quaternion& b) {
                return quaternion(
                    a.real * b.real - a.imaginary.x * b.imaginary.x - a.imaginary.y * b.imaginary.y - a.imaginary.z * b.imaginary.z,
                    a.real * b.imaginary.x + a.imaginary.x * b.real + a.imaginary.y * b.imaginary.z - a.imaginary.z * b.imaginary.y,
                    a.real * b.imaginary.y - a.imaginary.x * b.imaginary.z + a.imaginary.y * b.real + a.imaginary.z * b.imaginary.x,
                    a.real * b.imaginary.z + a.imaginary.x * b.imaginary.y - a.imaginary.y * b.imaginary.x + a.imaginary.z * b.real
                    );
            }

            friend const quaternion operator/(const quaternion& a, const quaternion& b) {
                return a * b.inverse();
            }

            const quaternion operator+=(const quaternion& q);
            const quaternion operator-=(const quaternion& q);
            const quaternion operator*=(const quaternion& q);
            const quaternion operator/=(const quaternion& q);

            vector3<complex<T>> imaginary = vector3<complex<T>>(0, 0, 0);
            T real = 0;
        };

        typedef quaternion<double> quaternion3d;
        typedef quaternion<float> quaternionf;
        typedef quaternion<int> quaternioni;
    }
}
