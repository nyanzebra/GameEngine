#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <list>

namespace ftl {
    namespace graphics {

        static const float MaxVerticalAngle = 85;

        class camera {
        public:
            camera() = default;
            ~camera() = default;

            const glm::mat4& projection() const;
            const glm::mat4& view() const;
            const glm::vec3& position() const;

            void projection(const glm::mat4& projection);
            void position(const glm::vec3& position);

            void look_at(const glm::vec3& center, const glm::vec3& up = glm::vec3(0, 1, 0));

            //void recalculate_matrices(const double& x, const double& y, const std::list<int>& keys);

        private:
            //quaternionf rotation;
            glm::mat4 _projection = glm::mat4(1);
            glm::mat4 _view = glm::mat4(1);
            glm::vec3 _position = glm::vec3(0, 0, 0);

            //default values
            float _mouse_speed = 0.005f;
            float _horizontal_angle = 3.14f;
            float _vertical_angle = 0.0f;
            float _initial_fov = 45.0f;
            float _speed = 3.0f;
        };
    }
}
