#pragma once

#include <vector>

//#include <freetype-gl.h>

#include "../renderer.h"

namespace ftl {
	namespace graphics {

//        typedef std::unique_ptr<ftgl::texture_atlas_t> unique_atlas;
        //typedef std::unique_ptr<ftgl::texture_font_t> unique_font;

		class Renderer2d : public Renderer {
		public:
			Renderer2d() { init(); }
			~Renderer2d() { glDeleteBuffers(1, &_vertex_buffer); }

			void start() override;
			void add(const game_object* renderable) override;
			void render() override;
			void finish() override;

		private:
			void init();

			
			GLsizei _index_count;

            //unique_atlas atlas;
            //unique_font font;
		};
	}
}
