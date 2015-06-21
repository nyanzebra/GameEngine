#include "window.h"

#include "../errors/glerror.h"

#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <glew.h>
#define GLFW_DLL
#include <glfw3.h>

using namespace cppe::graphics;
using namespace cppe::io;
using namespace cppe::math;

bool Window::init() {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3/n");
		return false;
	}
#if __APPLE__
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROfile, GLFW_OPENGL_CORE_PROfile);
#endif

	return true;
}

void Window::handleKeyPress(const int& key, const int& scancode, const int& action, const int& mods) {

}
void Window::handleMousePosition(const double& x_position, const double& y_position) {}
void Window::handleMouseClick(const int& button, const int& action, const int& mods) {}
void Window::handleScrollInput(const double& x_offset, const double& y_offset) {}
void Window::handleJoystickInput() {}
void Window::handleLeavingWindow(const int& entered) {}

bool Window::create(const char* window_name) {
	window = glfwCreateWindow(DEFAULT_WINDOW_SIZE, window_name, NULL, NULL);

	glfwSetWindowPos(window, DEFAULT_WINDOW_POSITION);

	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW/n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, this);

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {});

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		((Window*)glfwGetWindowUserPointer(window))->handleKeyPress(key, scancode, action, mods);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x_position, double y_position) {
		((Window*)glfwGetWindowUserPointer(window))->handleMousePosition(x_position, y_position);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		((Window*)glfwGetWindowUserPointer(window))->handleMouseClick(button, action, mods);
	});
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) { glfwSetWindowShouldClose(window, GL_TRUE); });

	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "ERROR: could not open window with GLEW/n");
		glfwTerminate();
		return false;
	}

	diagnositic();

	return true;
}

void Window::diagnositic() {
	console::setColorScheme(BLACK, WHITE);
	console::output_line("Renderer: ", glGetString(GL_RENDERER));
	console::output_line("OpenGL version supported: ", glGetString(GL_VERSION));
	console::output_line("Glew version supported: ", glewGetString(GLEW_VERSION));
	console::output_line("Glfw3 version supported: ", glfwGetVersionString());
	console::output_line();
}

void Window::add(const std::string& key, Scene* value) {
	scenes[key] = std::unique_ptr<Scene>(value);
}

Scene* Window::operator[](const std::string& key) {
	return scenes[key].get();
}

void Window::remove(const std::string& key) {
	scenes.erase(key);
}

void Window::setup() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_3D);
	glDepthFunc(GL_LESS);

	glClearColor(.5, .5, .5, 1);
	srand(time(NULL));
}

const vector2f Window::getCursorPosition() const {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return vector2f(x, y);
}

void Window::draw() {
	for (Scenes::iterator it = scenes.begin(); it != scenes.end(); ++it) {
		it->second->render();
	}

	frames_per_second++;
	if (frames_per_second_clock.time() - timer > 1.0f) {
		printf("%d fps\n", frames_per_second);
		timer += 1.0f;
		frames_per_second = 0;
	}
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window) == 1;
}

void Window::update() {
	GLError::errorCheck();
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void Window::position(const int& x, const int& y) {
	glfwSetWindowPos(window, x, y);
}

void Window::toggleFullScreen(const bool& on) {
	destroy();
}

void Window::toggleWindowedScreen(const bool& on) {

}

void Window::destroy() {
	for (Scenes::iterator it = scenes.begin(); it != scenes.end(); ++it) {
		it->second.release();
	}
	glfwDestroyWindow(window);
}