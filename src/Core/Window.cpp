#include "Window.h"

#include <iostream>

Window::Window(int width, int height, const std::string& title, WindowModes::Type wMode)
	: _window{ nullptr }, _width{ width }, _height{ height }, _title{ title }, _windowMode{ wMode }
{

}

Window::~Window()
{
	if (_window)
		glfwDestroyWindow(_window);
	glfwTerminate();
}

bool Window::Initialize()
{
	if (!glfwInit())
	{
		std::cout << "NOOOOO ERROR: GLFW failed to init.\n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = nullptr;
	switch (_windowMode)
	{
	case WindowModes::Type::FULLSCREEN:
		monitor = glfwGetPrimaryMonitor();
		break;
	case WindowModes::Type::BORDERLESS:
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		break;
	case WindowModes::Type::WINDOWED:
	default:
		break;
	}

	_window = glfwCreateWindow(_width, _height, _title.c_str(), monitor, nullptr);
	if (!_window)
	{
		std::cout << "NOOOOO ERROR: GLFW window failed.\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "NOOOOO ERROR: GLAD failed to init.\n";
		return false;
	}

	glViewport(0, 0, _width, _height);
	return true;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(_window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(_window);
}

void Window::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

