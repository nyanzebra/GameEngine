#include "label.h"

using namespace cppe::graphics;

Label::Label(const std::string& text, const vector4f& position, const vector3f& size, const vector4f& color) : text(text) {
    GameObject(position, size, color);
}

