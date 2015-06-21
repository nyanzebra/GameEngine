#pragma once

#include <glew.h>
#include <memory>
#include <stack>
#include <cstddef>

#include "gameobject.h"

#include "math/matrix.h"
#include "math/vector.h"

#include "buffer/buffer.h"

#include "extensions/console.h"

using namespace cppe::math;

namespace cppe {
	namespace graphics {
        struct MeshData {
            vector3f vertex;
            vector3f normal;
            vector2f texture_cooridinates;
            float texture_id = 0;
            unsigned int color = 0;
        };

#define MAX_SPRITES		60000
#define MAX_MODELS      10000
#define VERTEX_SIZE		sizeof(MeshData)
#define SPRITE_SIZE		VERTEX_SIZE * 4
#define BUFFER_SIZE		SPRITE_SIZE * MAX_SPRITES
#define INDICES_SIZE	MAX_SPRITES * 6

#define VERTEX_INDEX                0
#define TEXTURE_COORIDINATES_INDEX  1
#define TEXTURE_INDEX               2
#define COLOR_INDEX                 3
#define NORMALS_INDEX               4	

		class Renderer {
		public:
			Renderer() { transformation_stack.push(matrix4f::identity()); }
			~Renderer() = default;

			void push(const matrix4f& matrix);
			void pop();

			virtual void start() = 0;
			virtual void finish() = 0;

			virtual void add(const GameObject* renderable) = 0;

			virtual void render() = 0;
		protected:
			GLuint vertex_array;
            GLuint object_buffer;
            std::unique_ptr<IndexBuffer> index_buffer;
			bool can_render;
			std::stack<const matrix4f> transformation_stack;
		};		
	}
}
