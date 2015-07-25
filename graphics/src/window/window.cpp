#include "window.h"

#include "../errors/glerror.h"

#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

using namespace ftl::graphics;

bool window::init() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3/n");
        return false;
    }
#if __APPLE__
    glfwwindowHint(GLFW_SAMPLES, 4);
    glfwwindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwwindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwwindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwwindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    return true;
}

void window::handleKeyPress(const int& key, const int& scancode, const int& action, const int& mods) {

}
void window::handleMousePosition(const double& x_position, const double& y_position) {}
void window::handleMouseClick(const int& button, const int& action, const int& mods) {}
void window::handleScrollInput(const double& x_offset, const double& y_offset) {}
void window::handleJoystickInput() {}
void window::handleLeavingWindow(const int& entered) {}

bool window::create(const char* window_name) {
    _window = glfwCreateWindow(DEFAULT_WINDOW_SIZE, window_name, NULL, NULL);

    glfwSetWindowPos(_window, DEFAULT_WINDOW_POSITION);

    if (!_window) {
        fprintf(stderr, "ERROR: could not open window with GLFW/n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);

    glfwSetWindowUserPointer(_window, this);

    glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {});

    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        ((ftl::graphics::window*)glfwGetWindowUserPointer(window))->handleKeyPress(key, scancode, action, mods);
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x_position, double y_position) {
        ((ftl::graphics::window*)glfwGetWindowUserPointer(window))->handleMousePosition(x_position, y_position);
    });

    glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
        ((ftl::graphics::window*)glfwGetWindowUserPointer(window))->handleMouseClick(button, action, mods);
    });
    glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) { glfwSetWindowShouldClose(window, GL_TRUE); });

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

void window::diagnositic() {
    //cppe::io::console::setColorScheme(BLACK, WHITE);
    cppe::io::console::output_line("Renderer: ", glGetString(GL_RENDERER));
    cppe::io::console::output_line("OpenGL version supported: ", glGetString(GL_VERSION));
    cppe::io::console::output_line("Glew version supported: ", glewGetString(GLEW_VERSION));
    cppe::io::console::output_line("Glfw3 version supported: ", glfwGetVersionString());
    cppe::io::console::output_line();
}

void window::add(const std::string& key, scene* value) {
    _scenes[key] = std::unique_ptr<scene>(value);
}

scene* window::operator[](const std::string& key) {
    return _scenes[key].get();
}

void window::remove(const std::string& key) {
    _scenes.erase(key);
}

void window::setup(const Dimension& dimension) {
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    switch (dimension) {
    case Dimension::THREE:
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_CULL_FACE);
        break;
    case Dimension::TWO:
    default:
        break;
    }

    glClearColor(.5, .5, .5, 1);
    srand(time(NULL));
}

const glm::vec2 window::getCursorPosition() const {
    double x, y;
    glfwGetCursorPos(_window, &x, &y);
    return glm::vec2((float)x, (float)y);
}

void window::draw() {
    for (scenes::iterator it = _scenes.begin(); it != _scenes.end(); ++it) {
        std::list<int> keys;
        if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS)
            keys.push_back(GLFW_KEY_UP);
        if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS)
            keys.push_back(GLFW_KEY_DOWN);
        if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            keys.push_back(GLFW_KEY_RIGHT);
        if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
            keys.push_back(GLFW_KEY_LEFT);
        it->second->update_shader_variables(getCursorPosition().x, getCursorPosition().y);
//        it->second->adjust_camera(getCursorPosition().x, getCursorPosition().y, keys);
        it->second->render();
    }

    _frames_per_second++;
    if (_frames_per_second_clock.time() - _timer > 1.0f) {
        printf("%d fps\n", _frames_per_second);
        _timer++;
        _frames_per_second = 0;
    }
}

void window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool window::shouldClose() {
    return glfwWindowShouldClose(_window) == 1;
}

void window::update() {
    GLerror::errorCheck();
    glfwPollEvents();
    glfwSwapBuffers(_window);
}

void window::position(const int& x, const int& y) {
    glfwSetWindowPos(_window, x, y);
}

void window::toggleFullScreen(const bool& on) {
    destroy();
}

void window::toggleWindowedScreen(const bool& on) {

}

void window::destroy() {
    for (scenes::iterator it = _scenes.begin(); it != _scenes.end(); ++it) {
        it->second.release();
    }
    glfwDestroyWindow(_window);
}