#pragma once

#include <glm/glm.hpp>
#include <string>

namespace ftl {
    namespace graphics {
        struct vertex_data {
            vertex_data(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texture_coordinate) : _position(position), _normal(normal), _texture_coordinate(texture_coordinate) {}

            glm::vec3 _position;
            glm::vec3 _normal;
            glm::vec2 _texture_coordinate;
            //float _shininess;
            //vector4<char> _specular;
            float _texture_id = 0;
            unsigned int _color = 0;

            bool operator<(const vertex_data& that) const {
                return memcmp((void*)this, (void*)&that, sizeof(vertex_data)) > 0;
            }
        };
    }
}
