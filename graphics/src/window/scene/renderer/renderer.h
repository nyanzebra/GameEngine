#pragma once

#include <GL/glew.h>
#include <memory>
#include <stack>
#include <cstddef>

#include "gameobject.h"
#include "vertex_data.h"

#include <glm/gtc/matrix_transform.hpp>

#include "buffer/buffer.h"

#include "extensions/console.h"
                          
namespace ftl {
	namespace graphics {
#define MAX_SPRITES		60000
#define MAX_MODELS      10000
#define VERTEX_SIZE		sizeof(vertex_data)
#define SPRITE_SIZE		VERTEX_SIZE * 4
#define BUFFER_SIZE		SPRITE_SIZE * MAX_SPRITES
#define INDICES_SIZE	MAX_SPRITES * 6

#define VERTEX_INDEX                0
#define TEXTURE_COORIDINATES_INDEX  1
#define TEXTURE_ID_INDEX            2
#define COLOR_INDEX                 3
#define NORMALS_INDEX               4	

		class Renderer {
		public:
            Renderer() { _transformation_stack.push(glm::mat4()); }
			~Renderer() = default;

            void push(const glm::mat4& matrix);
			void pop();

			virtual void start() = 0;
			virtual void finish() = 0;

			virtual void add(const game_object* renderable) = 0;

			virtual void render() = 0;
		protected: 
            std::unique_ptr<IndexBuffer> _ib;

            vertex_data* _object_buffer;
            unsigned* _element_buffer;

            GLuint _index_buffer;
			GLuint _vertex_array;
            GLuint _vertex_buffer;

            std::vector<unsigned> _texture_slots;

			bool _can_render;

            std::stack<const glm::mat4> _transformation_stack;
		};		
	}
}
