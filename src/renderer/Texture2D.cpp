#include "Texture2D.h"

namespace Renderer {

	Texture2D::Texture2D(
		const GLuint width, 
		const GLuint height, 
		const unsigned char* data, 
		const unsigned int channels, 
		const GLenum filter, 
		const GLenum wrapMode) : width(width), height(height) {
		
		this->mode = GL_RGBA;
		
		if (channels == 3) {
			this->mode = GL_RGB;
		}
		
		glGenTextures(1, &this->id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->id);
		glTexImage2D(GL_TEXTURE_2D, 0, this->mode, width, height, 0, this->mode, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &this->id);
	}

	void Texture2D::bind() {
		glBindTexture(GL_TEXTURE_2D, this->id);
	}

}