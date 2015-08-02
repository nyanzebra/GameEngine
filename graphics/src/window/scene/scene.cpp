#include "scene.h"

#include "renderer/renderer.h"

using namespace ftl::graphics;

void scene::bind_shader(const ftl::graphics::shader& shader) {
    _shader = shader;
    _shader.enable();
}

void scene::attach_shader_variables() {
    _shader.uniform_Matrix4("projection_matrix", _camera.projection());
    _shader.uniform_Matrix4("view_matrix", _camera.view());
}             

void scene::update_shader_variables(const double& x, const double& y) {
    _shader.enable();
    _shader.uniform_floatx2("light_position", glm::vec2((float)(x * 32.0f / 800.0f) - 16.0f, (float)(9.0f - y * 18.0f / 600.0f)));
}

void scene::unbind_shader() {
    _shader.disable();
}

void scene::bind_renderer(const Dimension& dimension) {
    _renderer.release();
    switch (dimension) {
    case Dimension::TWO:
        _renderer = std::unique_ptr<Renderer>(new Renderer2d());
        break;
    case Dimension::MIXED:
        break;
    case Dimension::THREE:
        _renderer = std::unique_ptr<Renderer>(new Renderer3d());
        break;
    }
}

void scene::unbind_renderer() {
    _renderer.release();
}

void scene::projection_matrix(const glm::mat4& projection_matrix) {
    _projection_matrix = projection_matrix;
}

void scene::add_transform(const std::string& key, const glm::mat4& matrix) {
    _game_object_map[key].first = matrix * _last_transformation;
    _last_transformation = matrix * _last_transformation;
}

void scene::render() {
    _shader.enable();

    if (!_renderer) {
        cppe::io::console::output_line("ERROR:\trenderer does not exist!!");
    }
    _renderer->start();
    for (game_object_map::iterator it = _game_object_map.begin(); it != _game_object_map.end(); ++it) {
        if (!it->second.second.get()) {
            cppe::io::console::output_line("ERROR:\tgame object does not exist!!");
        }

        _renderer->push(it->second.first);
        _renderer->add(it->second.second.get());
        _renderer->pop();
    }
    _renderer->finish();

    _renderer->render();

    _shader.disable();
}

const game_object* scene::operator[](const std::string& key) {
    return _game_object_map[key].second.get();
}

void scene::add(const std::string& key, game_object* value) {
    _game_object_map[key] = { glm::mat4(), std::unique_ptr<game_object>(value) };
}

void scene::remove(const std::string& key) {
    _game_object_map.erase(key);
}
