#pragma once

#include <glew.h>

#include "extensions/console.h"

using namespace cppe::io;

class GLError {
public:
	static void errorCheck() {
		GLenum glError = glGetError();
		if (glError) {

			switch (glError) {
			case GL_INVALID_ENUM:
				console::output_line("ERROR:\tinvalid enum");
				break;

			case GL_INVALID_VALUE:
				console::output_line("ERROR:\tinvalid value");
				break;

			case GL_INVALID_OPERATION:
				console::output_line("ERROR:\tinvalid operation");

			default:
				console::output_line("ERROR:\tunknown");
				break;
			}
		}
	}
};
