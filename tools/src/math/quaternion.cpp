#include "quaternion.h"

#include <math.h>

using namespace cppe::math;

template <typename T = float>
const matrix4<T> quaternion<T>::as_matrix() const {
    matrix4 mat;
    mat.columns[0] = data;
    mat.columns[1] = vector4(data.x, -data.w, -data.z, data.y);
    mat.columns[2] = vector4(data.y, data.z, -data.w, -data.x);
    mat.columns[3] = vector4(data.z, -data.y, data.x, -data.w);
    return mat;
}

template <typename T = float>
const quaternion<T> quaternion<T>::operator+=(const quaternion<T>& q) {
    return *this = *this + q;
}

template <typename T = float>
const quaternion<T> quaternion<T>::operator-=(const quaternion<T>& q) {
    return *this = *this - q;
}

template <typename T = float>
const quaternion<T> quaternion<T>::operator*=(const quaternion<T>& q) {
    return *this = *this * q;
}

template <typename T = float>
const quaternion<T> quaternion<T>::operator/=(const quaternion<T>& q) {
    return *this = *this / q;
}
