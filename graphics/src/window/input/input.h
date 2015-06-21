#pragma once

#include <unordered_map>
#include <functional>

#ifdef _WIN32
#include "windows.h"
#endif
#include <glew.h>
#define GLFW_DLL
#include <glfw3.h>

namespace cppe {
	namespace graphics {

		class Input {
		public:
			Input() = default;
			~Input() { glfwDestroyCursor(cursor); }

			virtual void handleKeyPress(const int& key, const int& scancode, const int& action, const int& mods) = 0;
			virtual void handleMousePosition(const double& x_position, const double& y_position) = 0;
			virtual void handleMouseClick(const int& button, const int& action, const int& mods) = 0;
			virtual void handleScrollInput(const double& x_offset, const double& y_offset) = 0;
			virtual void handleJoystickInput() = 0;
			virtual void handleLeavingWindow(const int& entered) = 0;

			static const double getTimeInSeconds();
			static void setTimeInSeconds(const double& time);

			static void copy(GLFWwindow* window, const char* message);
			static const char* paste(GLFWwindow* window);

			static void hideCursor(GLFWwindow* window);
			static void showCursor(GLFWwindow* window);
			static void customCursor(GLFWwindow* window, const GLFWimage& image);

		private:
			static GLFWcursor* cursor;
		};
	}
}
