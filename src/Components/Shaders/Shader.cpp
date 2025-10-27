#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "glm/gtc/type_ptr.hpp"

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath)
	: _shaderProgramID(0), _vertexPath{ vertexPath }, _fragmentPath{ fragmentPath },
	_timeSinceLastCheck(0.f)
{
	ShaderProgramSource source = ParseShader(vertexPath, fragmentPath);
	_shaderProgramID = CreateShaderProgram(source.vertexSource, source.fragmentSource);

	_vertexTimeStamp = std::filesystem::last_write_time(_vertexPath);
	_fragmentTimeStamp = std::filesystem::last_write_time(_fragmentPath);
}

Shader::~Shader()
{
	GL_CHECK(glDeleteProgram(_shaderProgramID));
}

void Shader::Reload()
{
	ShaderProgramSource source = ParseShader(_vertexPath, _fragmentPath);
	unsigned int newProgram = CreateShaderProgram(source.vertexSource, source.fragmentSource);

	if (!newProgram)
		return;

	glDeleteProgram(_shaderProgramID);
	_shaderProgramID = newProgram;
	_uniformLocationCache.clear();
	std::cout << "Shader reloaded: " << _vertexPath << " / " << _fragmentPath << "\n";
}

bool Shader::NeedsReload() const
{
	return std::filesystem::last_write_time(_vertexPath) != _vertexTimeStamp ||
		std::filesystem::last_write_time(_fragmentPath) != _fragmentTimeStamp;
}

void Shader::ReloadChanges(float deltaTime)
{
	_timeSinceLastCheck += deltaTime;
	if (_timeSinceLastCheck < 1.f)
		return;

	if (NeedsReload())
	{
		Reload();
		_vertexTimeStamp = std::filesystem::last_write_time(_vertexPath);
		_fragmentTimeStamp = std::filesystem::last_write_time(_fragmentPath);
		std::cout << "[HOT RELOAD] Reloaded " << _vertexPath << " and " << _fragmentPath << "\n";
	}
	_timeSinceLastCheck = 0.f;
}

ShaderProgramSource Shader::ParseShader(std::string_view vertexPath, std::string_view fragmentPath)
{
	std::string vertCode;
	std::string fragCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	vShaderFile.open(std::string(vertexPath));
	fShaderFile.open(std::string(fragmentPath));

	if (!vShaderFile.is_open() || !fShaderFile.is_open())
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
		return ShaderProgramSource{ "", "" };
	}

	std::stringstream vShaderStream;
	std::stringstream fShaderStream;

	// read shader content from files
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	vShaderFile.close();
	fShaderFile.close();

	// convert stream into string
	vertCode = vShaderStream.str();
	fragCode = fShaderStream.str();

	return ShaderProgramSource{ vertCode, fragCode };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shader;
	// create empty shader
	GL_CHECK(shader = glCreateShader(type));
	// shader code to be loaded into the empty shader
	const char* shaderSource = source.c_str();
	GL_CHECK(glShaderSource(shader, 1, &shaderSource, nullptr));
	// compile the shader code
	GL_CHECK(glCompileShader(shader));
	// log shader
	LOG::LogShader(shader, type);

	return shader;
}

unsigned int Shader::CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int programID;
	// create program
	GL_CHECK(programID = glCreateProgram());
	// compile shaders
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	// attach shaders to program
	GL_CHECK(glAttachShader(programID, vs));
	GL_CHECK(glAttachShader(programID, fs));
	// link program and validate
	GL_CHECK(glLinkProgram(programID));
	GL_CHECK(glValidateProgram(programID));
	// log program
	LOG::LogProgram(programID);

	// clear shaders since already attached
	GL_CHECK(glDeleteShader(vs));
	GL_CHECK(glDeleteShader(fs));

	return programID;
}

void Shader::Bind() const
{
	GL_CHECK(glUseProgram(_shaderProgramID));
}

void Shader::Unbind() const
{
	GL_CHECK(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
		return _uniformLocationCache[name];

	int location;
	GL_CHECK(location = glGetUniformLocation(_shaderProgramID, name.c_str()));
	if (location == -1)
		std::cout << "AAAAAA WARNING: uniform " << name << " doesn't exist!\n";

	_uniformLocationCache[name] = location;
	return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GL_CHECK(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformVec4(const std::string& name, const glm::vec4& value)
{
	GL_CHECK(glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value)));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}
