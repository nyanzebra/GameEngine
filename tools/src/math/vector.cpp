#include "vector.h"

using namespace cppe::math;

template<typename T>
const float vector2<T>::magnitude() const {
	return sqrt((x * x) + (y * y));
}

template<typename T>
const float vector2<T>::dotProduct(const vector2<T>& vector) {
	return (x * vector.x) + (y * vector.y);
}

template<typename T>
const T vector2<T>::crossProduct(const vector2<T>& vector) {
    return x * vector.y - y * vector.x;
}

template<typename T>
const vector2<T> vector2<T>::unit() const {
    return vector2<T>(1, 1);
}

template<typename T>
void vector2<T>::scale(const float& scalar) {
	x *= scalar;
	y *= scalar;
}

template<typename T>
vector2<T>& vector2<T>::operator+=(const vector2<T>& vector) {
	return *this = *this + vector;
}

template<typename T>
vector2<T>& vector2<T>::operator-=(const vector2<T>& vector) {
	return *this = *this - vector;
}

template<typename T>
vector2<T>& vector2<T>::operator*=(const vector2<T>& vector) {
	return *this = *this * vector;
}

template<typename T>
vector2<T>& vector2<T>::operator/=(const vector2<T>& vector) {
	return *this = *this / vector;
}

template<typename T>
vector2<T>& vector2<T>::operator+=(const T& value) {
    return *this = *this + value;
}

template<typename T>
vector2<T>& vector2<T>::operator-=(const T& value) {
    return *this = *this - value;
}

template<typename T>
vector2<T>& vector2<T>::operator*=(const T& value) {
    return *this = *this * value;
}

template<typename T>
vector2<T>& vector2<T>::operator/=(const T& value) {
    return *this = *this / value;
}

//=============================================================

template<typename T>
const float vector3<T>::magnitude() const {
	return sqrt((x * x) + (y * y) + (z * z));
}

template<typename T>
const float  vector3<T>::dotProduct(const vector3<T>& vector) {
	return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

template<typename T>
const vector3<T>  vector3<T>::crossProduct(const vector3<T>& vector) {
	return vector3<T>(y * vector.z - z * vector.y, 
				   z * vector.x - x * vector.z, 
				   x * vector.y - y * vector.x);
}

template<typename T>
const vector3<T> vector3<T>::unit() const {
    return vector3<T>(1, 1, 1);
}

template<typename T>
void vector3<T>::scale(const float& scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

template<typename T>
vector3<T>& vector3<T>::operator+=(const vector3<T>& vector) {
	return *this = *this + vector;
}

template<typename T>
vector3<T>& vector3<T>::operator-=(const vector3<T>& vector) {
	return *this = *this - vector;
}

template<typename T>
vector3<T>& vector3<T>::operator*=(const vector3<T>& vector) {
	return *this = *this * vector;
}

template<typename T>
vector3<T>& vector3<T>::operator/=(const vector3<T>& vector) {
	return *this = *this / vector;
}

template<typename T>
vector3<T>& vector3<T>::operator+=(const T& value) {
    return *this = *this + value;
}

template<typename T>
vector3<T>& vector3<T>::operator-=(const T& value) {
    return *this = *this - value;
}

template<typename T>
vector3<T>& vector3<T>::operator*=(const T& value) {
    return *this = *this * value;
}

template<typename T>
vector3<T>& vector3<T>::operator/=(const T& value) {
    return *this = *this / value;
}

//=============================================================

template<typename T>
const float vector4<T>::magnitude() const {
	return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

template<typename T>
const float  vector4<T>::dotProduct(const vector4<T>& vector) {
	return (x * vector.x) + (y * vector.y) + (w * vector.w) + (z * vector.z);
}

template<typename T>
const vector4<T> vector4<T>::crossProduct(const vector4<T>& vector) {
    vector3<T> temp = vector3<T>(vector);
    vector3<T> as_3 = vector3<T>(*this);
    as_3.crossProduct(temp);

	return vector4<T>(as_3);
}

template<typename T>
const vector4<T> vector4<T>::unit() const {
    return vector4<T>(1, 1, 1, 1);
}

template<typename T>
void vector4<T>::scale(const float& scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
}

template<typename T>
vector4<T>& vector4<T>::operator+=(const vector4<T>& vector) {
	return *this = *this + vector;
}

template<typename T>
vector4<T>& vector4<T>::operator-=(const vector4<T>& vector) {
	return *this = *this - vector;
}

template<typename T>
vector4<T>& vector4<T>::operator*=(const vector4<T>& vector) {
	return *this = *this * vector;
}

template<typename T>
vector4<T>& vector4<T>::operator/=(const vector4<T>& vector) {
	return *this = *this / vector;
}

template<typename T>
vector4<T>& vector4<T>::operator+=(const T& value) {
    return *this = *this + value;
}

template<typename T>
vector4<T>& vector4<T>::operator-=(const T& value) {
    return *this = *this - value;
}

template<typename T>
vector4<T>& vector4<T>::operator*=(const T& value) {
    return *this = *this * value;
}

template<typename T>
vector4<T>& vector4<T>::operator/=(const T& value) {
    return *this = *this / value;
}
