#include "scene.h"

#include "renderer/renderer.h"

using namespace cppe::graphics;

void Scene::bindShader(Shader& shader) {
	shader.enable();
	shader.setUniformMatrix4("projection_matrix", matrix4f::orthographic(-16, 16, -9, 9, -1, 1));
	shader.disable();
	this->shader = shader;
}

void Scene::unbindShader() {
	shader.disable();

}

void Scene::bindRenderer(const Dimension& dimension) {
	renderer.release();
	switch (dimension) {
	case Dimension::TWO:
		renderer = std::unique_ptr<Renderer>(new Renderer2d());
		break;
	case Dimension::MIXED:
		break;
	case Dimension::THREE:
		renderer = std::unique_ptr<Renderer>(new Renderer3d());
		break;
	}
}

void Scene::unbindRenderer() {
	renderer.release();
}

void Scene::setProjectionmatrix(const matrix4f& projection_matrix) {
	this->projection_matrix = projection_matrix;
}

void Scene::add_transform(const std::string& key, const matrix4f& matrix) {
	gameobject_map[key].first = matrix * last_transformation;
	last_transformation = matrix * last_transformation;
}

void Scene::render() {
	shader.enable();

	if (!renderer) {
		console::output_line("ERROR:\trenderer does not exist!!");
	}
	renderer->start();
	for (GameObjectMap::iterator it = gameobject_map.begin(); it != gameobject_map.end(); ++it) {
		if (!it->second.second.get()) {
			console::output_line("ERROR:\tsprite does not exist!!");
		}
		renderer->push(it->second.first);
		renderer->add(it->second.second.get());
		renderer->pop();
	}
	renderer->finish();

	renderer->render();

	//shader.disable();
}

const GameObject* Scene::operator[](const std::string& key) {
	return gameobject_map[key].second.get();
}

void Scene::add(const std::string& key, GameObject* value) {
	gameobject_map[key] = { matrix4f::identity(), std::unique_ptr<GameObject>(value) };
}

void Scene::remove(const std::string& key) {
	gameobject_map.erase(key);
}
