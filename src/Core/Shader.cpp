#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	: _programID(0)
{
	ShaderProgramSource source = ParseShader(vertexPath, fragmentPath);
	std::cout << source.vertexSource << '\n' << source.fragmentSource << "\n";
	_programID = CreateShaderProgram(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	GL_CHECK(glDeleteProgram(_programID));
}

ShaderProgramSource Shader::ParseShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertCode;
	std::string fragCode;
	std::fstream vShaderFile;
	std::fstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
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
	}
	catch (std::ifstream::failure& err)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << err.what() << "\n";
	}

	return ShaderProgramSource{ vertCode.c_str(), fragCode.c_str() };
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
	GL_CHECK(glUseProgram(_programID));
}

void Shader::Unbind() const
{
	GL_CHECK(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& uniformName)
{
	if (_uniformLocationCache.find(uniformName) != _uniformLocationCache.end())
		return _uniformLocationCache[uniformName];

	int location;
	GL_CHECK(location = glGetUniformLocation(_programID, uniformName.c_str()));
	if (location == -1)
		std::cout << "AAAAAA WARNING: uniform " << uniformName << " doesn't exist!\n";

	_uniformLocationCache[uniformName] = location;
	return location;
}

void Shader::SetUniformVec4(const std::string uniformName, const glm::vec4& value)
{
	GL_CHECK(glUniform4fv(GetUniformLocation(uniformName), 1, glm::value_ptr(value)));
}
