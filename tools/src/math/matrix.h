#pragma once

#include "vector.h"

#include <assert.h>

namespace cppe {
    namespace math {
        template <typename T = float>
        class matrix4 { // Column-Major
        public:
            matrix4() {
                for (int i = 0; i < 16; ++i) {
                    elements[i] = 0;
                }
            }
            matrix4(const T& diagonal) {
                for (int i = 0; i < 16; ++i) {
                    if (i % 5 == 0) {
                        elements[i] = diagonal;
                    } else {
                        elements[i] = 0;
                    }
                }
            }
            ~matrix4() = default;

            static matrix4 identity() { return matrix4(1); }

            static matrix4 orthographic(const T& left, const T& right,
                const T& bottom, const T& top,
                const T& near, const T& far) {
                matrix4 resultant(1);

                resultant[0] = 2 / (right - left);
                resultant[5] = 2 / (top - bottom);
                resultant[10] = 2 / (near - far);
                resultant[12] = (left + right) / (left - right);
                resultant[13] = (bottom + top) / (bottom - top);
                resultant[14] = (far + near) / (far - near);

                return resultant;
            }

            static matrix4 perspective(const T& field_of_view, const T& aspect_ratio,
                const T& near, const T& far) {
                matrix4 resultant(1);

                resultant[0] = 1 / (aspect_ratio * tan(toRadians(field_of_view / 2.0f)));
                resultant[5] = 1 / tan(toRadians(field_of_view / 2.0f));
                resultant[10] = (-1 * (near + far)) / (near - far);
                resultant[11] = 1;
                resultant[14] = (2 * near * far) / (near - far);

                return resultant;
            }

            static matrix4 translation(const vector3<T>& translation) {
                matrix4 resultant(1);

                resultant[12] = translation.x;
                resultant[13] = translation.y;
                resultant[14] = translation.z;

                return resultant;
            }

            static matrix4 rotation(const T& angle, const vector3<T>& axis) {
                matrix4 resultant(1);

                T angle_radians = toRadians(angle);

                T cosine = cos(angle_radians);
                T sine = sin(angle_radians);

                T x = axis.x;
                T y = axis.y;
                T z = axis.z;

                resultant[0] = (x * x * (1 - cosine)) + cosine;
                resultant[1] = (y * x * (1 - cosine)) + (z * sine);
                resultant[2] = (z * x * (1 - cosine)) - (y * sine);

                resultant[4] = (x * y * (1 - cosine)) - (z * sine);
                resultant[5] = (y * y * (1 - cosine)) + cosine;
                resultant[6] = (z * y * (1 - cosine)) + (x * sine);

                resultant[8] = (x * z * (1 - cosine)) + (y * sine);
                resultant[9] = (y * z * (1 - cosine)) - (x * sine);
                resultant[10] = (z * z * (1 - cosine)) + cosine;

                return resultant;
            }

            static matrix4 scale(const vector3<T>& scalar) {
                matrix4 resultant(1);

                resultant[0] = scalar.x;
                resultant[5] = scalar.y;
                resultant[10] = scalar.z;

                return resultant;
            }

            T& operator[](const unsigned int& position) {
                assert(position < 16);
                return elements[position];
            }

            friend matrix4 operator*(matrix4 left, const matrix4& right) {
                return left.multiply(right);
            }

            matrix4& operator*=(const matrix4& matrix) {
                return *this = *this * matrix;
            }

            friend vector2<T> operator*(const matrix4& left, const vector2<T>& right) {
                return left.multiply(right);
            }

            friend vector3<T> operator*(const matrix4& left, const vector3<T>& right) {
                return left.multiply(right);
            }

            friend vector4<T> operator*(const matrix4& left, const vector4<T>& right) {
                return left.multiply(right);
            }

            union {
                T elements[4 * 4];
                struct {
                    vector4<T> columns[4];
                };
            };

        private:
            matrix4& multiply(const matrix4& matrix) {
                T data[16];
                for (int column = 0; column < 4; column++) {
                    for (int row = 0; row < 4; row++) {
                        T sum = 0;
                        for (int element = 0; element < 4; element++) {
                            sum += elements[row + element * 4] * matrix.elements[element + column * 4];
                        }
                        data[row + column * 4] = sum;
                    }
                }
                memcpy(elements, data, 4 * 4 * sizeof(T));

                return *this;
            }
            vector2<T> multiply(const vector2<T>& vector) const {
                return vector2<T>(
                    columns[0].x * vector.x + columns[1].x * vector.y + columns[2].x * 1 + columns[3].x * 1,
                    columns[0].y * vector.x + columns[1].y * vector.y + columns[2].y * 1 + columns[3].y * 1
                    );
            }

            vector3<T> multiply(const vector3<T>& vector) const {
                return vector3<T>(
                    columns[0].x * vector.x + columns[1].x * vector.y + columns[2].x * vector.z + columns[3].x * 1,
                    columns[0].y * vector.x + columns[1].y * vector.y + columns[2].y * vector.z + columns[3].y * 1,
                    columns[0].z * vector.x + columns[1].z * vector.y + columns[2].z * vector.z + columns[3].z * 1
                    );
            }


            vector4<T> multiply(const vector4<T>& vector) const {
                return vector4<T>(
                    columns[0].x * vector.x + columns[1].x * vector.y + columns[2].x * vector.z + columns[3].x * vector.w,
                    columns[0].y * vector.x + columns[1].y * vector.y + columns[2].y * vector.z + columns[3].y * vector.w,
                    columns[0].z * vector.x + columns[1].z * vector.y + columns[2].z * vector.z + columns[3].z * vector.w,
                    columns[0].w * vector.x + columns[1].w * vector.y + columns[2].w * vector.z + columns[3].w * vector.w
                    );
            }
        };

        typedef matrix4<complexi> matrix4ci;
        typedef matrix4<complexf> matrix4cf;
        typedef matrix4<complexd> matrix4cd;
        typedef matrix4<double> matrix43d;
        typedef matrix4<float> matrix4f;
        typedef matrix4<int> matrix4i;
    }
}
