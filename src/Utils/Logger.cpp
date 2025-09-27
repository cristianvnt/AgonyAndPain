#include "Logger.h"

#include <iostream>

void LOG::LogShader(unsigned int shader, unsigned int type)
{
	int success;
	GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (success)
		return;

	char infoLog[512];

	GL_CHECK(glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog));

	const char* typeStr = [&]()
		{
			switch (type)
			{
			case GL_VERTEX_SHADER:
				return "VERTEX";
				break;
			case GL_FRAGMENT_SHADER:
				return "FRAGMENT";
				break;
			default:
				return "UNKNOWN";
			}
		}();
	std::cerr << "ERROR::SHADER::" << typeStr << "::COMPILATION_FAILED\n" << infoLog << "\n";
}

void LOG::LogProgram(unsigned int programID)
{
	int success;
	GL_CHECK(glGetProgramiv(programID, GL_LINK_STATUS, &success));
	if (success)
		return;

	char infoLog[512];
	GL_CHECK(glGetProgramInfoLog(programID, sizeof(infoLog), nullptr, infoLog));
	std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
}

void ERROR::glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool ERROR::glCheckError_(const char* func, const char* file, int line)
{
	while (GLenum err = glGetError())
	{
		std::cerr << "[OpenGL] " << GetGLErrorString(err) << " | " << func << "\n | " << file << " (" << line << ")\n";
		return false;
	}
	return true;
}

constexpr const char* ERROR::GetGLErrorString(GLenum err)
{
	switch (err)
	{
	case GL_INVALID_ENUM:
		return "INVALID_ENUM";
	case GL_INVALID_VALUE:
		return "INVALID_VALUE";
	case GL_INVALID_OPERATION:
		return "INVALID_OPERATION";
	case GL_STACK_UNDERFLOW:
		return "STACK_UNDERFLOW";
	case GL_STACK_OVERFLOW:
		return "STACK_OVERFLOW";
	case GL_OUT_OF_MEMORY:
		return "OUT_OF_MEMORY";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "INVALID_FRAMEBUFFER_OPERATION";
	default:
		return "UNKNOWN_GL_ERROR";
	}
}