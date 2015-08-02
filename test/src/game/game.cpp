#include <test/testsuite.h>

#include <window/window.h>
#include <window/scene/renderer/gameobject.h>

#include <window/scene/renderer/2d/sprite.h>
#include <window/scene/renderer/2d/renderer2d.h>

#include "window/scene/renderer/3d/model.h"
#include "window/scene/renderer/3d/renderer3d.h"

#include <errors/glerror.h>

using namespace cppe::test;
using namespace cppe::io;
using namespace cppe::math;
using namespace ftl::graphics;

#define SKIP_3D 0
#define SKIP_2D 0

TEST_SUITE(game) {

    TEST("2d") {
#if SKIP_2D
        return;
#endif

        window window;
        window.create("So Yeon!!!");

        window.setup(Dimension::TWO);

        shader shader("../game/src/resources/shaders/test2d.vert", "../game/src/resources/shaders/test2d.frag");

        window.add("Button", new scene());

        window["Button"]->bind_shader(shader);

        window["Button"]->camera().projection(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

        window["Button"]->attach_shader_variables();

        window["Button"]->bind_renderer(Dimension::TWO);

        window["Button"]->add("button_background", new sprite(glm::vec2(0, 0), 0, glm::vec2(7, 4), glm::vec4(1, 1, 1, 1)));
        window["Button"]->add_transform("button_background", glm::translate(glm::mat4(), glm::vec3(7, 1, 0)));

        window["Button"]->add("button_foreground", new sprite(glm::vec2(0, 0), 0.5, glm::vec2(7 / 2, 4 / 2), glm::vec4(.5, 0.5, 1, 1)));
        window["Button"]->add_transform("button_foreground", glm::translate(glm::mat4(), glm::vec3(.5, .5, 0)));

        window["Button"]->add("button_text", new sprite(glm::vec2(0, 0), 1, glm::vec2(7 / 4, 4 / 4), glm::vec4(1, 0.5, 1, 1)));
        window["Button"]->add_transform("button_text", glm::translate(glm::mat4(), glm::vec3(.5, .5, 0)));

        texture image("../game/src/resources/textures/test.png", Dimension::TWO, Aliasing::ON, false);

        (*(sprite*)(*window["Button"])["button_text"]).texture(image);

        GLint texture_ids[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        shader.uniform_int_vectorx1("textures", 10, texture_ids);

        while (!window.shouldClose()) {
            window.clear();

            window.draw();

            window.update();
        }

        window["Button"]->unbind_renderer();
        window["Button"]->unbind_shader();

        shader.disable();

        window.destroy();
    };

    TEST("3d") {
#if SKIP_3D
        return;
#endif

        window window;
        window.create("3d So Yeon!!!");

        window.setup(Dimension::THREE);

        shader shader("../game/src/resources/shaders/3d.vert", "../game/src/resources/shaders/3d.frag");

        texture image("../game/src/resources/textures/test.png", Dimension::TWO, Aliasing::ON, false);

        mesh cube;
        cube.load("../game/src/resources/models/cube.obj");

        material nothing;
        nothing.texture(image);

        window.add("3d cube", new scene());

        window["3d cube"]->bind_shader(shader);

        window["3d cube"]->camera().projection(glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 100.0f));
        window["3d cube"]->camera().position(glm::vec3(0, 0, 6));
        window["3d cube"]->camera().look_at(glm::vec3(0, 0, 0));

        window["3d cube"]->attach_shader_variables();

        window["3d cube"]->bind_renderer(Dimension::THREE);

        window["3d cube"]->add("cube", new model(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec4(1, 0, 1, 1), cube, nothing));
        window["3d cube"]->add_transform("cube", glm::rotate(glm::mat4(), 45.0f, glm::vec3(3, 1, 3)));

        GLint texture_ids[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        shader.uniform_int_vectorx1("textures", 10, texture_ids);

        while (!window.shouldClose()) {
            window.clear();

            window.draw();

            window.update();
        }

        window["3d cube"]->unbind_renderer();
        window["3d cube"]->unbind_shader();

        shader.disable();

        window.destroy();
    };

};
