#include "sprite.h"

using namespace ftl::graphics;

const ftl::graphics::texture& sprite::texture() const {
	return _texture;
}

void sprite::texture(const ftl::graphics::texture& texture) {
	_texture = texture;
	_texture.bind();
}

const std::array<glm::vec2, 4>& sprite::coordinates() const {
	return _coordinates;
}

void sprite::coordinates(const std::array<glm::vec2, 4>& coordinates) {
	_coordinates = coordinates;
}
