#include "camera.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "../../constants.h"

using namespace ftl::graphics;

const glm::mat4& camera::projection() const {
    return _projection;
}

const glm::mat4& camera::view() const {
    return _view;
}

const glm::vec3& camera::position() const {
    return _position;
}

void camera::projection(const glm::mat4& projection) {
    _projection = projection;
}
void camera::position(const glm::vec3& position) {
    _position = position;
}

void camera::look_at(const glm::vec3& center, const glm::vec3& up) {
    _view = glm::lookAt(_position, center, up);
}

//void camera::recalculate_matrices(const double& x, const double& y, const std::list<int>& keys) {
//
//    // glfwGetTime is called only once, the first time this function is called
//    static double lastTime = glfwGetTime();
//
//    // Compute time difference between current and last frame
//    double currentTime = glfwGetTime();
//    float deltaTime = float(currentTime - lastTime);
//
//    // Compute new orientation
//    _horizontal_angle += _mouse_speed * float(DEFAULT_WINDOW_SIZE_X / 2 - x);
//    _vertical_angle += _mouse_speed * float(DEFAULT_WINDOW_SIZE_Y / 2 - y);
//
//    // Direction : Spherical coordinates to Cartesian coordinates conversion
//    glm::vec3 direction(cos(_vertical_angle) * sin(_horizontal_angle), sin(_vertical_angle), cos(_vertical_angle) * cos(_horizontal_angle));
//
//    // Right vector
//    glm::vec3 right = glm::vec3(sin(_horizontal_angle - 3.14f / 2.0f), 0, cos(_horizontal_angle - 3.14f / 2.0f));
//
//    // Up vector
//    glm::vec3 up = glm::cross(right, direction);
//
//    for (int key : keys) {
//        switch (key) {
//        case GLFW_KEY_UP:
//            _position += direction * deltaTime * _speed;
//            break;
//        case GLFW_KEY_DOWN:
//            _position -= direction * deltaTime * _speed;
//            break;
//        case GLFW_KEY_RIGHT:
//            _position += right * deltaTime * _speed;
//            break;
//        case GLFW_KEY_LEFT:
//            _position -= right * deltaTime * _speed;
//            break;
//        default:
//            break;
//        }
//    }
//
//    float FoV = _initial_fov;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
//
//    // Camera matrix
//    _view = lookAt(_position, _position + direction, -up);
//
//    // For the next frame, the "last time" will be "now"
//    lastTime = currentTime;
//}
