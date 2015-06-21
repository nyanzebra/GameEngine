#pragma once

#include <map>

#include "scene/scene.h"

#include "math/timer.h"

namespace cppe {
	namespace graphics {
#define DEFAULT_WINDOW_SIZE 800, 600
#define DEFAULT_WINDOW_POSITION 5, 30
#define DEFAULT_WINDOW_SIZE_X 800.0f
#define DEFAULT_WINDOW_SIZE_Y 600.0f

		typedef std::map<std::string, std::unique_ptr<Scene>> Scenes;

		class Window {
		public:
			Window() { init(); };
			~Window() {	glfwTerminate(); }

			bool create(const char* window_name);

			void setup();

			void clear();

			void update();

			bool shouldClose();

			void draw();

			void add(const std::string& key, Scene* value);

			Scene* operator[](const std::string& key);

			void remove(const std::string& key);

			void toggleFullScreen(const bool& on);

			void toggleWindowedScreen(const bool& on);

			void position(const int& x, const int& y);

			void cursor(const char* file_name);

			const vector2f getCursorPosition() const;

			void destroy();
			
			Scenes scenes;

			void handleKeyPress(const int& key, const int& scancode, const int& action, const int& mods);
			void handleMousePosition(const double& x_position, const double& y_position);
			void handleMouseClick(const int& button, const int& action, const int& mods);
			void handleScrollInput(const double& x_offset, const double& y_offset);
			void handleJoystickInput();
			void handleLeavingWindow(const int& entered);

		private:
			bool init();
			void diagnositic();

			Timer frames_per_second_clock;
			unsigned int frames_per_second = 0;
			unsigned int timer = 0;
			GLFWwindow* window;
		};
	}
}
