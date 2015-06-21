#include "sprite.h"

using namespace cppe::graphics;

const Texture& Sprite::getTexture() const {
	return texture;
}

void Sprite::setTexture(const Texture& texture) {
	this->texture = texture;
	this->texture.bind();
}

const std::array<vector2f, 4>& Sprite::getCooridinates() const {
	return cooridinates;
}

void Sprite::setCoordinates(const std::array<vector2f, 4>& cooridinates) {
	this->cooridinates = cooridinates;
}
