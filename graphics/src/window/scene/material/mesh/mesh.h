#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

namespace ftl {
    namespace graphics {

        class mesh {
        public:
            mesh() = default;
            mesh(const mesh&& mesh) : _normals(mesh._normals), _vertices(mesh._vertices), _coordinates(mesh._coordinates) {}
            ~mesh() = default;

            void load(const std::string& resource_name);

            const std::vector<unsigned int>& indices() const;

            const std::vector<glm::vec3>& normals() const;
            const std::vector<glm::vec3>& vertices() const;
            const std::vector<glm::vec2>& coordinates() const;

            void normals(const std::vector<glm::vec3>& normals);
            void vertices(const std::vector<glm::vec3>& vertices);
            void coordinates(const std::vector<glm::vec2>& coordinates);

        private:
            const std::vector<glm::vec3> extract(const std::string& file_data, unsigned& counter, const std::string& T) const;
            const std::string extract_line(const std::string& file_data, unsigned& counter) const;
            const std::vector<unsigned> extract_faces(const std::string& file_data, unsigned& counter) const;
            void indexer();

            std::vector<glm::vec3> _normals;
            std::vector<glm::vec3> _vertices;
            std::vector<glm::vec2> _coordinates;
            std::vector<unsigned int> _indices;
        };

    }
}