#pragma once

namespace game {
	enum Game_Type {
		FPS,
		RTS,
		CASUAL,
		RPG,
		MMO,

	};
	class Mesh {

	};
	class Texture {

	};
	class Game_Object {
	public:
		Game_Object() {}
		~Game_Object() {}

	protected:
		void render();
		void draw();
		void update();
	};
	class Entity : public Game_Object {

	};
	class Level : public Game_Object {

	};
	class Menu : public Game_Object {

	};
	class Game_State {

	};
	class Game {
	public:
		Game();
		~Game();

		void start();
		void save();
		void quit();
	};

#define ENTITY(sub_name)
}

namespace gameapi {

}