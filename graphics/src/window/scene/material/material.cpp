#include "material.h"

using namespace ftl::graphics;

const ftl::graphics::texture& material::texture() const {
	return _texture;
}

const ftl::graphics::shader& material::shader() const {
	return _shader;
}

void material::shader(const ftl::graphics::shader& shader) {
	_shader = shader;
	_shader.enable(); 
}
void material::texture(const ftl::graphics::texture& texture) {
	_texture = texture;
    _texture.bind();
}
	 