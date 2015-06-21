#pragma once

#include "../renderer.h"

namespace cppe {
	namespace graphics {
		class Renderer3d : public Renderer {
		public:
			Renderer3d() = default;
			~Renderer3d() = default;

            void init();

			void start() override {}
			void add(const GameObject* renderable) {}
			void render() override {}
			void finish() override {}
		};
	}
}
