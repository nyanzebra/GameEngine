#pragma once

#include <glm/glm.hpp>

namespace ftl {
    namespace graphics {
        class game_object {
        public:
            game_object() = default;
            game_object(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
            ~game_object() = default;

            const unsigned& color() const;
            void color(const glm::vec4& color);


            const glm::vec3& position() const;
            void position(const glm::vec3& position);

            const glm::vec3& size() const;
            void size(const glm::vec3& size);

        protected:
            unsigned _color;
            glm::vec3 _position;
            glm::vec3 _size;
        };
    }
}
