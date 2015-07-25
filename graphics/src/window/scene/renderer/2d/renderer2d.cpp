#include "renderer2d.h"
#include "sprite.h"

using namespace ftl::graphics;

void Renderer2d::init() {

    glGenVertexArrays(1, &_vertex_array);
    glGenBuffers(1, &_vertex_buffer);

    glBindVertexArray(_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(VERTEX_INDEX);
    glEnableVertexAttribArray(TEXTURE_COORIDINATES_INDEX);
    glEnableVertexAttribArray(TEXTURE_ID_INDEX);
    glEnableVertexAttribArray(COLOR_INDEX);

    glVertexAttribPointer(VERTEX_INDEX,
        3,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_SIZE,
        (const GLvoid*)0);
    glVertexAttribPointer(TEXTURE_COORIDINATES_INDEX,
        2,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_SIZE,
        (const GLvoid*)(offsetof(vertex_data, vertex_data::_texture_coordinate)));
    glVertexAttribPointer(TEXTURE_ID_INDEX,
        1,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_SIZE,
        (const GLvoid*)(offsetof(vertex_data, vertex_data::_texture_id)));
    glVertexAttribPointer(COLOR_INDEX,
        4,
        GL_UNSIGNED_BYTE,
        GL_TRUE,
        VERTEX_SIZE,
        (const GLvoid*)(offsetof(vertex_data, vertex_data::_color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint* indices = new GLuint[INDICES_SIZE];

    for (unsigned int i = 0, j = 0; i < INDICES_SIZE; i += 6, j += 4) {
        indices[i + 0] = j + 0;
        indices[i + 1] = j + 1;
        indices[i + 2] = j + 2;
        indices[i + 3] = j + 2;
        indices[i + 4] = j + 3;
        indices[i + 5] = j + 0;
    }

    std::unique_ptr<IndexBuffer> ib(new IndexBuffer(indices, INDICES_SIZE));
    _ib = std::move(ib);

    if (!_index_buffer) {
        cppe::io::console::output_line("ERROR:\tfailed to init index buffer");
    }

    _index_count = 0;

    glBindVertexArray(0);

    //atlas = unique_atlas(std::move(texture_atlas_new(512, 512, 1)));
    //font = unique_font(std::move(texture_font_new_from_file(atlas.get(), 20, "")));
}

void Renderer2d::start() {
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    _object_buffer = (vertex_data*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (!_object_buffer) {
        cppe::io::console::output_line("ERROR:\tfailed to map to buffer");
    }
    _can_render = true;
}

void Renderer2d::add(const game_object* renderable) {
    if (!_can_render) {
        cppe::io::console::output_line("ERROR:\taction(s) was/were not sorrounded with start and finish");
    }

    const glm::vec3& size = renderable->size();
    const glm::vec3& position = renderable->position();
    const unsigned& color = renderable->color();
    const std::array<glm::vec2, 4>& texture_cooridinates = ((sprite*)renderable)->coordinates();
    const unsigned int texture_id = ((sprite*)renderable)->texture().ID();

    float texture_slot = 0.0f;
    if (texture_id > 0) {
        bool is_found = false;
        for (unsigned int i = 0; i < _texture_slots.size(); i++) {
            if (_texture_slots[i] == texture_id) {
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
            _texture_slots.push_back(texture_id);
            texture_slot = (float)_texture_slots.size() - 1;
        }
    }

    _object_buffer->_position = glm::vec3(_transformation_stack.top() * glm::vec4(position.x, position.y, position.z, 0));
    _object_buffer->_texture_coordinate = texture_cooridinates[0];
    _object_buffer->_texture_id = texture_slot;
    _object_buffer->_color = color;
    _object_buffer++;

    _object_buffer->_position = glm::vec3(_transformation_stack.top() * glm::vec4(position.x, position.y + size.y, position.z, 0));
    _object_buffer->_texture_coordinate = texture_cooridinates[1];
    _object_buffer->_texture_id = texture_slot;
    _object_buffer->_color = color;
    _object_buffer++;

    _object_buffer->_position = glm::vec3(_transformation_stack.top() * glm::vec4(position.x + size.x, position.y + size.y, position.z, 0));
    _object_buffer->_texture_coordinate = texture_cooridinates[2];
    _object_buffer->_texture_id = texture_slot;
    _object_buffer->_color = color;
    _object_buffer++;

    _object_buffer->_position = glm::vec3(_transformation_stack.top() * glm::vec4(position.x + size.x, position.y, position.z, 0));
    _object_buffer->_texture_coordinate = texture_cooridinates[3];
    _object_buffer->_texture_id = texture_slot;
    _object_buffer->_color = color;
    _object_buffer++;

    _index_count += 6;
}

void Renderer2d::finish() {
    if (glUnmapBuffer(GL_ARRAY_BUFFER) != GL_TRUE) {
        cppe::io::console::output_line("ERROR:\tgl map is corrupted");
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _can_render = false;
}

void Renderer2d::render() {

    for (unsigned int i = 0; i < _texture_slots.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _texture_slots[i]);
    }

    glBindVertexArray(_vertex_array);

    _ib->bind();
    glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, NULL);
    _ib->unbind();

    glBindVertexArray(0);

    _index_count = 0;
}

