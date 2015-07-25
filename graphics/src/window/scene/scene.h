#pragma once

#include <map>
#include <string>
#include <memory>

#include "renderer/renderer.h"
#include "renderer/gameobject.h"

#include "renderer/2d/sprite.h"
#include "renderer/2d/renderer2d.h"

#include "renderer/3d/model.h"
#include "renderer/3d/renderer3d.h"

#include "..\camera\camera.h"

#include "../input/Input.h"

#include "extensions/console.h"

#include "configurables.h"

namespace ftl {
	namespace graphics {

        typedef std::map<std::string, std::pair<glm::mat4, std::unique_ptr<game_object>>> game_object_map;

		class scene {
		public:
			scene() = default;
			virtual ~scene() = default;

			void render();

			void bind_shader(const shader& shader);
            void attach_shader_variables();
            void update_shader_variables(const double& x, const double& y);
			void unbind_shader();

			void bind_renderer(const Dimension& dimension);
			void unbind_renderer();

			void add(const std::string& key, game_object* value);

			void remove(const std::string& key);

            void add_transform(const std::string& key, const glm::mat4& matrix);

			shader& shader();

			const game_object* operator[](const std::string& key);

            ftl::graphics::camera& camera() { return _camera; }

            //void adjust_camera(const double& x, const double& y, const std::list<int>& keys) { _camera.recalculate_matrices(x, y, keys); }

            void projection_matrix(const glm::mat4& projection_matrix);

		private:
            ftl::graphics::camera _camera;
			std::unique_ptr<Renderer> _renderer;
			ftl::graphics::shader _shader;
            glm::mat4 _projection_matrix;
            glm::mat4 _last_transformation = glm::mat4();
			game_object_map _game_object_map;
		};
	}
}
