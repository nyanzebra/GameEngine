#include "material.h"

using namespace cppe::graphics;

Texture& Material::getTexture() {
	return texture;
}
Shader& Material::getShader() {
	return shader;
}

void Material::setShader(const Shader& shader) {
	this->shader = shader;
	this->shader.enable();
	this->shader.setUniformMatrix4("projection_matrix", matrix4f::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
	this->shader.disable();
}
void Material::setTexture(const Texture& texture) {
	this->texture = texture;
}
	 