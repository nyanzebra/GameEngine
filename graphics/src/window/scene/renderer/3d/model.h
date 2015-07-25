#pragma once

#include <list>

#include "../gameobject.h"

#include "../../material/material.h"
#include "../../material/mesh/mesh.h"
                         
namespace ftl {
    namespace graphics {
        class model : public game_object {
        public:
            model() = default;
            model(const model&& model) : _mesh(model._mesh), _material(model._material) {}
            model(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const mesh& mesh, const material& material)
                : game_object(glm::vec3(position), size, color), _mesh(mesh), _material(material) {}
            ~model() = default;

            const ftl::graphics::material& material() const;
            const ftl::graphics::mesh& mesh() const;

            void material(const ftl::graphics::material& material);
            void mesh(const ftl::graphics::mesh& mesh);

        private:
            ftl::graphics::mesh _mesh;

            ftl::graphics::material _material;
        };
    }
}
