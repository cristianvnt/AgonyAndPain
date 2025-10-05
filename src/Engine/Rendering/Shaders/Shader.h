#ifndef SHADER_H
#define SHADER_H

#include "glm/glm.hpp"

#include "Engine/Utils/Logger.h"

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	unsigned int _shaderProgramID;
	std::unordered_map<std::string, int> _uniformLocationCache;

	ShaderProgramSource ParseShader(std::string_view vertexPath, std::string_view fragmentPath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

public:
	Shader() : _shaderProgramID(0) {}
	Shader(std::string_view vertexPath, std::string_view fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	int GetUniformLocation(const std::string& name);

	void SetUniform1i(const std::string& name, int value);
	void SetUniformVec4(const std::string& name, const glm::vec4& value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};

#endif