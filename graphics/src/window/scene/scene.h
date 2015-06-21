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

#include "../input/Input.h"

#include "extensions/console.h"

#include "configurables.h"

using namespace cppe::io;

namespace cppe {
	namespace graphics {

		typedef std::map<std::string, std::pair<matrix4f, std::unique_ptr<GameObject>>> GameObjectMap;

		class Scene {
		public:
			Scene() = default;
			virtual ~Scene() = default;

			void render();

			void bindShader(Shader& shader);
			void unbindShader();

			void bindRenderer(const Dimension& dimension);
			void unbindRenderer();

			void add(const std::string& key, GameObject* value);

			void remove(const std::string& key);

			void add_transform(const std::string& key, const matrix4f& matrix);

			Shader& getShader();

			const GameObject* operator[](const std::string& key);

			void setProjectionmatrix(const matrix4f& projection_matrix);

		private:
			std::unique_ptr<Renderer> renderer;
			Shader shader;
			matrix4f projection_matrix;
			matrix4f last_transformation = matrix4f::identity();
			GameObjectMap gameobject_map;
		};
	}
}
