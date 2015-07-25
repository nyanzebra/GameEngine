#include "gameobject.h"

using namespace ftl::graphics;

game_object::game_object(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
    : _position(position), _size(size) {
    game_object::color(color);
}

void game_object::color(const glm::vec4& color) {
    int red = (int)(color.x * 255.0f);
    int green = (int)(color.y * 255.0f);
    int blue = (int)(color.z * 255.0f);
    int alpha = (int)(color.w * 255.0f);

    unsigned color_code = alpha << 24 | blue << 16 | green << 8 | red;

    _color = color_code;
}

const unsigned& game_object::color() const {
    return _color;
}

void game_object::position(const glm::vec3& position) {
    _position = position;
}

const glm::vec3& game_object::position() const {
    return _position;
}

void game_object::size(const glm::vec3& size) {
    _size = size;
}

const glm::vec3& game_object::size() const {
    return _size;
}
