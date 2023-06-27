#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class ShaderProgram;
	class Texture2D;
};

class ResourceManager {
private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap shaders;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap textures;
	std::string executablePath;
	std::string getFileContent(const std::string&);

public:
	ResourceManager(const std::string&);
	~ResourceManager() = default;
	ResourceManager() = delete;
	ResourceManager(ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string&, const std::string&, const std::string&);
	std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string&);
	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string&, const std::string&);
	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string&);
};