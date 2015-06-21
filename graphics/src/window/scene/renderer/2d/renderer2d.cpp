#include "renderer2d.h"
#include "sprite.h"

using namespace cppe::graphics;
using namespace cppe::io;

void Renderer2d::init() {

	glGenVertexArrays(1, &vertex_array);
	glGenBuffers(1, &object_buffer);

	glBindVertexArray(vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, object_buffer);
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(VERTEX_INDEX);
	glEnableVertexAttribArray(TEXTURE_COORIDINATES_INDEX);
	glEnableVertexAttribArray(TEXTURE_INDEX);
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
						  (const GLvoid*)(offsetof(MeshData, MeshData::texture_cooridinates)));
	glVertexAttribPointer(TEXTURE_INDEX,
						  1,
						  GL_FLOAT,
						  GL_FALSE,
						  VERTEX_SIZE,
						  (const GLvoid*)(offsetof(MeshData, MeshData::texture_id)));
	glVertexAttribPointer(COLOR_INDEX, 
						  4, 
						  GL_UNSIGNED_BYTE,
						  GL_TRUE, 
						  VERTEX_SIZE, 
						  (const GLvoid*)(offsetof(MeshData, MeshData::color)));

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
	index_buffer = std::move(ib);

	if (!index_buffer) {
		console::output_line("ERROR:\tfailed to init index buffer");
	}

	index_count = 0;

	glBindVertexArray(0);

    atlas = unique_atlas(std::move(texture_atlas_new(512, 512, 1)));
    font = unique_font(std::move(texture_font_new_from_file(atlas.get(), 20, "")));
}

void Renderer2d::start() {
	glBindBuffer(GL_ARRAY_BUFFER, object_buffer);
	vertices_buffer = (MeshData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (!vertices_buffer) {
		console::output_line("ERROR:\tfailed to map to buffer");
	}
	can_render = true;
}


void Renderer2d::add(const GameObject* renderable) {
	if (!can_render) {
		console::output_line("ERROR:\taction(s) was/were not sorrounded with start and finish");
	}

	const vector3f& size = renderable->getSize();
	const vector4f& position = renderable->getPosition();
	const unsigned& color = renderable->getColor();
	const std::array<vector2f, 4>& texture_cooridinates = ((Sprite*)renderable)->getCooridinates();
	const unsigned int texture_id = ((Sprite*)renderable)->getTexture().getID();

	float texture_slot = 0.0f;
	if (texture_id > 0) {
		bool is_found = false;
		for (int i = 0; i < texture_slots.size(); i++) {
			if (texture_slots[i] == texture_id) {
				texture_slot = (float)(i + 1);
				is_found = true;
				break;
			}
		}

		if (!is_found) {
			if (texture_slots.size() >= 16) {
				finish();
				render();
				start();
			}
			texture_slots.push_back(texture_id);
			texture_slot = (float)texture_slots.size();
		}
	}

	vertices_buffer->vertex = transformation_stack.top() * vector3f(position.x, position.y, position.z);
	vertices_buffer->texture_cooridinates = texture_cooridinates[0];
	vertices_buffer->texture_id = texture_slot;
	vertices_buffer->color = color;
	vertices_buffer++;

	vertices_buffer->vertex = transformation_stack.top() * vector3f(position.x, position.y + size.y, position.z);
	vertices_buffer->texture_cooridinates = texture_cooridinates[1];
	vertices_buffer->texture_id = texture_slot;
	vertices_buffer->color = color;
	vertices_buffer++;

	vertices_buffer->vertex = transformation_stack.top() * vector3f(position.x + size.x, position.y + size.y, position.z);
	vertices_buffer->texture_cooridinates = texture_cooridinates[2];
	vertices_buffer->texture_id = texture_slot;
	vertices_buffer->color = color;
	vertices_buffer++;

	vertices_buffer->vertex = transformation_stack.top() * vector3f(position.x + size.x, position.y, position.z);
	vertices_buffer->texture_cooridinates = texture_cooridinates[3];
	vertices_buffer->texture_id = texture_slot;
	vertices_buffer->color = color;
	vertices_buffer++;

	index_count += 6;
}

void Renderer2d::finish() {
	if (glUnmapBuffer(GL_ARRAY_BUFFER) != GL_TRUE) {
		console::output_line("ERROR:\tgl map is corrupted");
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	can_render = false;
}

void Renderer2d::render() {

	for (int i = 0; i < texture_slots.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture_slots[i]);
	}

	glBindVertexArray(vertex_array);

	index_buffer->bind();
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, NULL);
	index_buffer->unbind();

	glBindVertexArray(0);

	index_count = 0;
}

