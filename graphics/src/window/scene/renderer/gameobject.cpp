#include "gameobject.h"

using namespace cppe::graphics;

GameObject::GameObject(const vector4f& position, const vector3f& size, const vector4f& color)
	: position(position), size(size) {
	int red = (int) color.x * 255.0f;
    int green = (int) color.y * 255.0f;
    int blue = (int) color.z * 255.0f;
    int alpha = (int) color.w * 255.0f;

	this->color = alpha << 24 | blue << 16 | green << 8 | red;
}

void GameObject::setColor(const vector4f& color) {
	int red = color.x * 255.0f;
	int green = color.y * 255.0f;
	int blue = color.z * 255.0f;
	int alpha = color.w * 255.0f;

	unsigned color_code = alpha << 24 | blue << 16 | green << 8 | red;

	this->color = color_code;
}

const unsigned& GameObject::getColor() const {
	return color;
}

void GameObject::setPosition(const vector4f& position) {
	this->position = position;
}

const vector4f& GameObject::getPosition() const {
	return position;
}

void GameObject::setSize(const vector3f& size) {
	this->size = size;
}

const vector3f& GameObject::getSize() const {
	return size;
}
