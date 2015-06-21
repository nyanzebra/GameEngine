#pragma once

#include "../gameobject.h"

namespace cppe {
    namespace graphics {
        class Label : public GameObject {
        public:
            Label(const std::string& text, const vector4f& position, const vector3f& size, const vector4f& color);
            ~Label() = default;

        private:
            std::string text;
        };
    }
}
