#pragma once

#include <vector>

#include <freetype-gl.h>

#include "../renderer.h"

namespace cppe {
	namespace graphics {

        typedef std::unique_ptr<ftgl::texture_atlas_t> unique_atlas;
        typedef std::unique_ptr<ftgl::texture_font_t> unique_font;

		class Renderer2d : public Renderer {
		public:
			Renderer2d() { init(); };
			~Renderer2d() { glDeleteBuffers(1, &object_buffer); }

			void start() override;
			void add(const GameObject* renderable) override;
			void render() override;
			void finish() override;

		private:
			void init();

			std::vector<unsigned> texture_slots;
			GLsizei index_count;
			MeshData* vertices_buffer;

            unique_atlas atlas;
            unique_font font;
		};
	}
}
