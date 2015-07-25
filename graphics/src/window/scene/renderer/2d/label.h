#pragma once

#include "../gameobject.h"

namespace ftl {
    namespace graphics {
        class Label : public game_object {
        public:
            Label(const std::string& text, const glm::vec4& position, const glm::vec3& size, const glm::vec4& color) : _text(text) {
                game_object(position, size, color);
            }
            ~Label() = default;

        private:
            std::string _text;
        };
    }
}
