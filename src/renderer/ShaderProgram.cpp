#include "ShaderProgram.h"

#include <iostream>

namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertex, const std::string& fragment) {
        GLuint vId;
        if (!this->createShader(vertex, GL_VERTEX_SHADER, vId)) {
            std::cerr << "VERTEX SHADER compile time error" << std::endl;
            return;
        }

        GLuint fId;
        if (!this->createShader(fragment, GL_FRAGMENT_SHADER, fId)) {
            std::cerr << "FRAGMENT SHADER compile time error" << std::endl;
            glDeleteShader(vId);
            return;
        }

        this->id = glCreateProgram();
        glAttachShader(this->id, vId);
        glAttachShader(this->id, fId);
        glLinkProgram(this->id);

        GLint successLink = 0;
        glGetProgramiv(id, GL_LINK_STATUS, &successLink);

        if (!successLink) {
            GLchar info[1024];
            glGetProgramInfoLog(this->id, 1024, nullptr, info);
            std::cerr << "ERROR:SHADER: Link: \n" << info << std::endl;
        } else {
            this->compiled = true;
        }

        glDeleteShader(vId);
        glDeleteShader(fId);
	}

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(this->id);
    }

    void ShaderProgram::use() {
        glUseProgram(this->id);
    }

    bool ShaderProgram::isCompiled() {
        return this->compiled;
    }

    bool ShaderProgram::createShader(const std::string& code, const GLenum type, GLuint& id) {
        id = glCreateShader(type);
        const char* source = code.c_str();
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (!success) {
            GLchar info[1024];
            glGetShaderInfoLog(id, 1024, nullptr, info);
            std::cerr << "ERROR:SHADER: Compile: \n" << info << std::endl;
            return false;
        }

        return true;
    }
}