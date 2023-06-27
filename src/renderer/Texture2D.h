#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	class Texture2D {
	private:
		GLuint width;
		GLuint height;
		GLuint id;
		GLenum mode;

	public:
		Texture2D(const GLuint, const GLuint, const unsigned char*, const unsigned int = 4, const GLenum = GL_LINEAR, const GLenum = GL_CLAMP_TO_EDGE);
		~Texture2D();
		void bind();
	};
}