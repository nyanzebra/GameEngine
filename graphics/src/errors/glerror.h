#pragma once

#ifdef _NULL_IMPORT_DESCRIPTOR
#undef _NULL_IMPORT_DESCRIPTOR
#endif
#include <GL/glew.h>

#include "extensions/console.h"
                
class GLerror {
public:
	static void errorCheck() {
		GLenum glError = glGetError();
		if (glError) {

			switch (glError) {
			case GL_INVALID_ENUM:
				cppe::io::console::output_line("ERROR:\tinvalid enum");
				break;

			case GL_INVALID_VALUE:
                cppe::io::console::output_line("ERROR:\tinvalid value");
				break;

			case GL_INVALID_OPERATION:
                cppe::io::console::output_line("ERROR:\tinvalid operation");

			default:
                cppe::io::console::output_line("ERROR:\tunknown");
				break;
			}
		}
	}
};
