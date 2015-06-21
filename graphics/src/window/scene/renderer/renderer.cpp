#include "renderer.h"

using namespace cppe::graphics;

void Renderer::push(const matrix4f& matrix) {
	transformation_stack.push(transformation_stack.top() * matrix);
}

void Renderer::pop() {
	if (transformation_stack.size() > 1) {
		transformation_stack.pop();
	}
}
