#pragma once

#include <map>

#include "scene/scene.h"

#include "math/timer.h"

#include "../constants.h"

namespace ftl {
	namespace graphics {        
		typedef std::map<std::string, std::unique_ptr<scene>> scenes;

		class window {
		public:
			window() { init(); };
			~window() {	glfwTerminate(); }

			bool create(const char* window_name);

			void setup(const Dimension& dimension);

			void clear();

			void update();

			bool shouldClose();

			void draw();

			void add(const std::string& key, scene* value);

			scene* operator[](const std::string& key);

			void remove(const std::string& key);

			void toggleFullScreen(const bool& on);

			void toggleWindowedScreen(const bool& on);

			void position(const int& x, const int& y);

			void cursor(const char* file_name);

            const glm::vec2 getCursorPosition() const;

			void destroy();
			
			scenes _scenes;

			void handleKeyPress(const int& key, const int& scancode, const int& action, const int& mods);
			void handleMousePosition(const double& x_position, const double& y_position);
			void handleMouseClick(const int& button, const int& action, const int& mods);
			void handleScrollInput(const double& x_offset, const double& y_offset);
			void handleJoystickInput();
			void handleLeavingWindow(const int& entered);

		private:
			bool init();
			void diagnositic();

			cppe::math::Timer _frames_per_second_clock;
			unsigned int _frames_per_second = 0;
			unsigned int _timer = 0;
			GLFWwindow* _window;
		};
	}
}
