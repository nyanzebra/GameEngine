#include "window/window.h"

#include "window/scene/renderer/renderer.h"
#include "window/scene/renderer/gameobject.h"

#include "window/scene/renderer/2d/sprite.h"
#include "window/scene/renderer/2d/renderer2d.h"

#include "window/scene/renderer/3d/model.h"
#include "window/scene/renderer/3d/renderer3d.h"

using namespace cppe::io;
using namespace cppe::graphics;

int main(int argc, const char* argv[]) {
	Window window;
	window.create("So Yeon!!!");

	window.setup();

	Shader shader("src/resources/shaders/test2d.vert", "src/resources/shaders/test2d.frag");
	shader.enable();
	shader.setUniformFloatx2("light_position", vector2f(-15, 5));

    Model cube;
    cube.load("src/resources/models/test.obj");

	window.add("Button", new Scene()); 
	window["Button"]->bindShader(shader);
	window["Button"]->bindRenderer(Dimension::TWO);

	window["Button"]->add("button_background", new Sprite(0, 0, 0, 7, 4, vector4f(1, 1, 1, 1)));
	window["Button"]->add_transform("button_background", matrix4f::translation(vector3f(-15, 1, 0)));
	
	window["Button"]->add("button_foreground", new Sprite(0, 0, 0.5, 7 / 2, 4 / 2, vector4f(.5, 0.5, 1, 1)));
	window["Button"]->add_transform("button_foreground", matrix4f::translation(vector3f(.5, .5, 0)));

	window["Button"]->add("button_text", new Sprite(0, 0, 1, 7 / 4, 4 / 4, vector4f(1, 0.5, 1, 1)));
	window["Button"]->add_transform("button_text", matrix4f::translation(vector3f(.5, .5, 0)));

	Texture image("src/resources/textures/test.png", 
				  Dimension::TWO, 
				  Aliasing::ON,
				  false);

	(*(Sprite*)(*window["Button"])["button_text"]).setTexture(image);
	Sprite a = (*(Sprite*)(*window["Button"])["button_text"]);

	shader.enable();
	GLint texture_ids[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	shader.setUniformIntvectorx1("textures", 10, texture_ids);

	while (!window.shouldClose()) {
		window.clear();

		float x = window.getCursorPosition().x;
		float y = window.getCursorPosition().y;
		shader.enable();
		shader.setUniformFloatx2("light_position", vector2f((float)(x * 32.0f / 800.0f) - 16.0f, (float)(9.0f - y * 18.0f / 600.0f)));
		
		window.draw();
		window.update();
	}

	window["Button"]->unbindRenderer();
	window["Button"]->unbindShader();

	shader.disable();

	window.destroy();
	return 0;
}