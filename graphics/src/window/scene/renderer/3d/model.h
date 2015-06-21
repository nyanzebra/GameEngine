#pragma once

#include <list>

#include "math/vector.h"
#include "../../material/material.h"

using namespace cppe::math;

namespace cppe {
    namespace graphics {
        class Model {
        public:
            Model() = default;
            Model(const Model&& Model) : Model_vertices(Model.Model_vertices), material(Model.material), texture_vertices(Model.texture_vertices) {}
            ~Model() = default;

            void load(const std::string& resource_name);

            void bindVertices(const vector3f vertices[], const unsigned& number_of_vertices);

            void bindMaterial(const Material& material, const vector3f vertices[], const unsigned& number_of_vertices);

            const std::list<vector3f> getModelVertices() const;

            const std::list<vector3f> getTextureVertices() const;

            void addModelVertex(const vector3f& vertex);

            void addTextureVertex(const vector3f& vertex);

            const Material& getMaterial() const;

        private:
            const std::vector<vector3f> extract(const std::string& file_data, unsigned& counter, const std::string& T) const;
            const std::string extract_line(const std::string& file_data, unsigned& counter) const;
            const std::vector<unsigned> extract_faces(const std::string& file_data, unsigned& counter) const;


            std::list<vector3f> Model_vertices;
            std::list<vector3f> texture_vertices;
            Material material;
        };
    }
}
