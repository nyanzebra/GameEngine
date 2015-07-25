#include "renderer.h"

using namespace ftl::graphics;

void Renderer::push(const glm::mat4& matrix) {
	_transformation_stack.push(_transformation_stack.top() * matrix);
}

void Renderer::pop() {
	if (_transformation_stack.size() > 1) {
		_transformation_stack.pop();
	}
}
