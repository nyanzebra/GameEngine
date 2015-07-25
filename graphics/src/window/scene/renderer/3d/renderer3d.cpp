#include "renderer3d.h"
#include "model.h"

#include "../../../../errors/glerror.h"

using namespace ftl::graphics;

void Renderer3d::init() {
    glGenVertexArrays(1, &_vertex_array);
    glBindVertexArray(_vertex_array);

    glGenBuffers(1, &_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MAX_MODELS, NULL, GL_STREAM_DRAW);

    glEnableVertexAttribArray(VERTEX_INDEX);
    glEnableVertexAttribArray(TEXTURE_COORIDINATES_INDEX);
    glEnableVertexAttribArray(TEXTURE_ID_INDEX);
    glEnableVertexAttribArray(COLOR_INDEX);
    glEnableVertexAttribArray(NORMALS_INDEX);

    glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)0);
    glVertexAttribPointer(TEXTURE_COORIDINATES_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(vertex_data, vertex_data::_texture_coordinate)));
    glVertexAttribPointer(TEXTURE_ID_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(vertex_data, vertex_data::_texture_id)));
    glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (const GLvoid*)(offsetof(vertex_data, vertex_data::_color)));
    glVertexAttribPointer(NORMALS_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(vertex_data, vertex_data::_normal)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    _indices_count = 0;

    glBindVertexArray(0);
}

void Renderer3d::start() {
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);

    _object_buffer = (vertex_data*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    _element_buffer = (unsigned*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

    if (!_object_buffer) {
        cppe::io::console::output_line("ERROR:\tfailed to map to buffer");
    }

    _can_render = true;
}

void Renderer3d::add(const game_object* object) {
    if (!_can_render) {
        cppe::io::console::output_line("ERROR:\taction(s) was/were not sorrounded with start and finish");
    }
    model* temp = (model*)object;

    const glm::vec3& size = temp->size();
    const glm::vec3& position = temp->position();
    const unsigned& color = temp->color();

    const GLuint& id = temp->material().texture().ID();
    
    const std::vector<glm::vec3>& vertices = temp->mesh().vertices();
    const std::vector<glm::vec3>& normals = temp->mesh().normals();
    const std::vector<glm::vec2>& coordinates = temp->mesh().coordinates();
    const std::vector<unsigned int>& indices = temp->mesh().indices();

    float texture_slot = 0.0f;
    if (id > 0) {
        bool is_found = false;
        for (unsigned int i = 0; i < _texture_slots.size(); i++) {
            if (_texture_slots[i] == id) {
                texture_slot = (float)(i + 1);
                is_found = true;
                break;
            }
        }

        if (!is_found) {
            if (_texture_slots.size() >= 16) {
                finish();
                render();
                start();
            }
            _texture_slots.push_back(id);
            texture_slot = (float)_texture_slots.size() - 1;
        }
    }

    for (int i = 0; i < vertices.size(); ++i) {
        _object_buffer->_position = glm::vec3(_transformation_stack.top() * glm::vec4(vertices[i] + position, 0));
        _object_buffer->_normal = glm::vec3(_transformation_stack.top() * glm::vec4(normals[i], 0));
        _object_buffer->_texture_coordinate = coordinates[i];
        _object_buffer->_texture_id = texture_slot;
        _object_buffer->_color = color;
        _object_buffer++;
    }

    _indices_count += vertices.size();

    for (int i = 0; i < indices.size(); ++i) {
        *_element_buffer = indices[i];
        _element_buffer++;
    }
}

void Renderer3d::finish() {
    if (glUnmapBuffer(GL_ARRAY_BUFFER) != GL_TRUE) {
        cppe::io::console::output_line("ERROR:\tgl map is corrupted");
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) != GL_TRUE) {
        cppe::io::console::output_line("ERROR:\tgl map is corrupted");
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    _can_render = false;
}

void Renderer3d::render() {

    for (unsigned int i = 0; i < _texture_slots.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _texture_slots[i]);
    }

    glBindVertexArray(_vertex_array);

    //glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
    //glDrawArrays(GL_TRIANGLES, 0, _indices_count);
    glDrawElements(GL_TRIANGLE_STRIP, 3 * _indices_count, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLerror::errorCheck();
    glBindVertexArray(0);

    _indices_count = 0;
}
