#pragma once

#include "math.h"

#include <ostream>

namespace cppe {
    namespace math {
        template <typename T = float>
        class complex {
        public:
            complex() = default;
            complex(const T& real) : real(real), imaginary(0) {}
            complex(const T& real, const T& imaginary) : real(real), imaginary(imaginary) {}
            complex(const complex<T>& com) : real(com.real), imaginary(com.imaginary) {}
            ~complex() = default;

            const bool operator==(const complex<T>& value) const {
                return (real == value.real && imaginary == value.imaginary);
            }

            const bool operator!=(const complex<T>& value) const {
                return !(*this == value);
            }

            friend std::ostream& operator<<(std::ostream& stream, const complex& value) {
                if (value.imaginary >= 0) {
                    stream << "complex: " << value.real << "+" << value.imaginary << "i";
                } else {
                    stream << "complex: " << value.real << "-" << value.imaginary << "i";
                }
                return stream;
            }

            friend complex operator+(complex left, const complex& right) {
                left.real += right.real;
                left.imaginary += right.imaginary;

                return left;
            }

            friend complex operator-(complex left, const complex& right) {
                left.real -= right.real;
                left.imaginary -= right.imaginary;

                return left;
            }

            friend complex operator*(complex left, const complex& right) {
                T a, b, c, d;
                a = left.real * right.real;
                b = left.real * right.imaginary;
                c = left.imaginary * right.real;
                d = left.imaginary * right.imaginary;

                left.real = a + (d * -1);
                left.imaginary = b + c;

                return left;
            }

            friend complex operator/(complex left, const complex& right) {
                complex conjugate = complex(right.real, -1 * right.imaginary);
                complex divisor = right * conjugate;
                left = left * conjugate;

                return left / divisor.real;
            }

            friend complex operator+(complex left, const T& right) {
                left.real += right;
                left.imaginary += right;

                return left;
            }

            friend complex operator-(complex left, const T& right) {
                left.real -= right;
                left.imaginary -= right;

                return left;
            }

            friend complex operator*(complex left, const T& right) {
                left.real *= right;
                left.imaginary *= right;

                return left;
            }

            friend complex operator/(complex left, const T& right) {
                left.real /= right;
                left.imaginary /= right;

                return left;
            }

            const T square() const {
                return (to_square(real) + (-1) * to_square(imaginary));
            }

            complex& operator+=(const complex& com) {
                return *this = *this + com;
            }

            complex& operator-=(const complex& com) {
                return *this = *this - com;
            }

            complex& operator*=(const complex& com) {
                return *this = *this * com;
            }

            complex& operator/=(const complex& com) {
                return *this = *this / com;
            }


            complex& operator+=(const T& value){
                return  *this = *this + value;
            }

            complex& operator-=(const T& value){
                return  *this = *this - value;
            }

            complex& operator*=(const T& value){
                return  *this = *this * value;
            }

            complex& operator/=(const T& value){
                return  *this = *this / value;
            }

            T real, imaginary;
        };

        typedef complex<float> complexf;
        typedef complex<int> complexi;
        typedef complex<double> complexd;
    }
}
