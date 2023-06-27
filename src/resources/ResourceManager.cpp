#include "ResourceManager.h"
#include "../renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executablePath) {
	size_t index = executablePath.find_last_of("/\\");
	this->executablePath = executablePath.substr(0, index);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShader(const std::string& name, const std::string& vertex, const std::string& fragment) {
	const std::string vCode = this->getFileContent(vertex);

	if (vCode.empty()) {
		std::cerr << "ERROR::RESOURCE_MANAGER Can't load vertex shder" << std::endl;
		return nullptr;
	}

	const std::string fCode = this->getFileContent(fragment);

	if (fCode.empty()) {
		std::cerr << "ERROR::RESOURCE_MANAGER Can't load fragment shder" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram> result = this->shaders.emplace(name, std::make_shared<Renderer::ShaderProgram>(vCode, fCode)).first->second;
	
	if (result->isCompiled()) {
		return result;
	}

	std::cerr << "ERROR::RESOURCE_MANAGER Shader is not compiled" << std::endl;
	return nullptr;
}

std::string ResourceManager::getFileContent(const std::string& file) {
	std::ifstream f;
	f.open(this->executablePath + "/" + file, std::ios::in | std::ios::binary);
	if (!f.is_open()) {
		std::cerr << "Cannot read resource " << file << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShader(const std::string& name) {
	ShaderProgramsMap::iterator iter = this->shaders.find(name);
	if (iter != this->shaders.end()) {
		return iter->second;
	}

	std::cerr << "Can't find shader " << name << std::endl;
	return nullptr;
}