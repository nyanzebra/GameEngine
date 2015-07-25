#pragma once

#include "../renderer.h"

namespace ftl {
	namespace graphics {
		class Renderer3d : public Renderer {
		public:
            Renderer3d() { init(); }
            ~Renderer3d() { glDeleteBuffers(1, &_vertex_buffer); /* glDeleteBuffers(1, &_coordinate_buffer);*/ glDeleteBuffers(1, &_normal_buffer); }

            void init();

            void start() override;
            void add(const game_object* renderable) override;
            void render() override;
            void finish() override;
        private:
            unsigned int _indices_count = 0;
            //GLuint _coordinate_buffer;
            GLuint _normal_buffer;

		};
	}
}
