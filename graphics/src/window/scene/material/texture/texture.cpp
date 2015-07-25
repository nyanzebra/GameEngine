#include "texture.h"

#include "extensions/file.h"
#include "extensions/console.h"

#include <FreeImage.h>

#include "../../../../errors/glerror.h"

using namespace ftl::graphics;

texture::texture(const std::string& resource_name, const Dimension& dimension, const Aliasing& aliasing, const bool& generate_mipmap) : _dimension(dimension) {
	if (_texture == 0 && !load(resource_name, dimension, aliasing, generate_mipmap)) {
		cppe::io::console::output_line("ERROR:\tfailed to read file... ", resource_name);
	}
}

const GLuint& texture::ID() const {
	return _texture;
}

BYTE* texture::load_image(const char* resource_name, unsigned* width, unsigned* height) {
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib = nullptr;
	fif = FreeImage_GetFileType(resource_name, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(resource_name);
	if (fif == FIF_UNKNOWN)
		return nullptr;

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, resource_name);
	if (!dib)
		return nullptr;

	BYTE* pixels = FreeImage_GetBits(dib);
	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);
	int bits = FreeImage_GetBPP(dib);

	int size = *width * *height * (bits / 8);
	BYTE* result = new BYTE[size];
	memcpy(result, pixels, size);
	FreeImage_Unload(dib);
	return result;
}

const bool texture::load(const std::string& resource_name, const Dimension& dimension, const Aliasing& aliasing, const bool& generate_mipmap) {
	_image._name = resource_name.c_str();

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib = nullptr;

	fif = FreeImage_GetFileType(resource_name.c_str(), 0);

	if (fif == FIF_UNKNOWN) {
		fif = FreeImage_GetFIFFromFilename(resource_name.c_str());
	}
	if (fif == FIF_UNKNOWN) {
		return false;
	}

	if (FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_Load(fif, resource_name.c_str());
	}
	if (!dib) {
		return false;
	}

	_image._width = FreeImage_GetWidth(dib);
	_image._height = FreeImage_GetHeight(dib);
	_image._bits_per_pixel = FreeImage_GetBPP(dib);
	int size = _image._width * _image._height * (_image._bits_per_pixel / 8);
	BYTE* pixels = FreeImage_GetBits(dib);
	_image._data = new BYTE[size];
	memcpy(_image._data, pixels, size);
	
	glGenTextures(1, &_texture);
	configure(dimension, aliasing);
    FreeImage_Unload(dib);
	GLerror::errorCheck();

	return true;
}

void texture::configure(const Dimension& dimension, const Aliasing& aliasing) {
	switch (dimension) {
	case Dimension::TWO:
		configure_dimension(GL_TEXTURE_2D, aliasing);
		if (_image._bits_per_pixel == 32) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _image._width, _image._height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)_image._data);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image._width, _image._height, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)_image._data);
		}
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
        break;
	case Dimension::THREE:
        configure_dimension(GL_TEXTURE_2D, aliasing);
        if (_image._bits_per_pixel == 32) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _image._width, _image._height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)_image._data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image._width, _image._height, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)_image._data);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
		/*configure_dimension(GL_TEXTURE_3D, aliasing);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTeximage3D(GL_TEXTURE_3D, 0, GL_RGBA, _image._width, _image._height, image.depth, GL_BGRA, GL_UNSIGNED_BYTE, _image._data);
		glBindtexture(GL_TEXTURE_3D, 0);*/
		break;
	}
}
void texture::configure_dimension(const int& dimension, const Aliasing& aliasing) {
	switch (aliasing) {
	case Aliasing::OFF:
		glBindTexture(dimension, _texture);
		configure_alias(dimension, GL_LINEAR);
		break;
	case Aliasing::ON:
		glBindTexture(dimension, _texture);
		configure_alias(dimension, GL_NEAREST);
	}
}
void texture::configure_alias(const int& dimension, const int& aliasing) {
	glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, aliasing);
	glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, aliasing);
}

const image& texture::image() const {
	return _image;
}

void texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, _texture);
}

void texture::unbind() const {
	glDeleteTextures(1, &_texture);
}
