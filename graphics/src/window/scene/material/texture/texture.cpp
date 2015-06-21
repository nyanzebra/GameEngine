#include "texture.h"

#include "extensions/file.h"
#include "extensions/console.h"

#include <FreeImage.h>

#include "../../../../errors/glerror.h"

using namespace cppe::graphics;
using namespace cppe::io;

Texture::Texture(const std::string& resource_name, const Dimension& dimension, const Aliasing& aliasing, const bool& generate_mipmap) : dimension(dimension) {
	if (texture == 0 && !load(resource_name, dimension, aliasing, generate_mipmap)) {
		console::output_line("ERROR:\tfailed to read file... ", resource_name);
	}
}

const GLuint& Texture::getID() const {
	return texture;
}

BYTE* Texture::load_image(const char* resource_name, unsigned* width, unsigned* height) {
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

const bool Texture::load(const std::string& resource_name, const Dimension& dimension, const Aliasing& aliasing, const bool& generate_mipmap) {
	image.name = resource_name.c_str();

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

	image.width = FreeImage_GetWidth(dib);
	image.height = FreeImage_GetHeight(dib);
	image.bits_per_pixel = FreeImage_GetBPP(dib);
	int size = image.width * image.height * (image.bits_per_pixel / 8);
	BYTE* pixels = FreeImage_GetBits(dib);
	image.data = new BYTE[size];
	memcpy(image.data, pixels, size);
	
	glGenTextures(1, &texture);
	configure(dimension, aliasing);
    FreeImage_Unload(dib);
	GLError::errorCheck();

	return true;
}

void Texture::configure(const Dimension& dimension, const Aliasing& aliasing) {
	switch (dimension) {
	case Dimension::TWO:
		configure_dimension(GL_TEXTURE_2D, aliasing);
		if (image.bits_per_pixel == 32) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)image.data);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)image.data);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		break;
	case Dimension::THREE:
		/*configure_dimension(GL_TEXTURE_3D, aliasing);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, image.width, image.height, image.depth, GL_BGRA, GL_UNSIGNED_BYTE, image.data);
		glBindTexture(GL_TEXTURE_3D, 0);*/
		break;
	}
}
void Texture::configure_dimension(const int& dimension, const Aliasing& aliasing) {
	switch (aliasing) {
	case Aliasing::OFF:
		glBindTexture(dimension, texture);
		configure_alias(dimension, GL_LINEAR);
		break;
	case Aliasing::ON:
		glBindTexture(dimension, texture);
		configure_alias(dimension, GL_NEAREST);
	}
}
void Texture::configure_alias(const int& dimension, const int& aliasing) {
	glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, aliasing);
	glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, aliasing);
}

const Image& Texture::getImage() const {
	return image;
}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() const {
	glDeleteTextures(1, &texture);
}
