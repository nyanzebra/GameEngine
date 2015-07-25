#include "input.h"

using namespace ftl::graphics;

GLFWcursor* Input::cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);

const double Input::getTimeInSeconds() {
	return glfwGetTime();
}
void Input::setTimeInSeconds(const double& time) {
	glfwSetTime(time);
}

void Input::copy(GLFWwindow* window, const char* message) {
	glfwSetClipboardString(window, message);
}
const char* Input::paste(GLFWwindow* window) {
	return glfwGetClipboardString(window);
}

void Input::hideCursor(GLFWwindow* window) { 
	glfwSetCursor(window, NULL); 
}
void Input::showCursor(GLFWwindow* window) { 
	glfwSetCursor(window, cursor); 
}
void Input::customCursor(GLFWwindow* window, const GLFWimage& image) {
	cursor = glfwCreateCursor(&image, 0, 0);
	glfwSetCursor(window, cursor);
}