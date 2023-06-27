#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	class ShaderProgram {
	private:
		bool compiled = false;
		GLuint id = 0;

		bool createShader(const std::string&, const GLenum, GLuint&);
	public:
		ShaderProgram(const std::string&, const std::string&);
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram operator=(const ShaderProgram&) = delete;
		~ShaderProgram();
		bool isCompiled();
		void use();
		void setTexture(const std::string&, const GLuint);
	};
}