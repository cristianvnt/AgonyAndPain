#include "Window.h"

#include <iostream>

#include "Utils/Logger.h"

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

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	GL_CHECK(glViewport(0, 0, width, height));
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
	glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);

	glfwSwapInterval(0);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "NOOOOO ERROR: GLAD failed to init.\n";
		return false;
	}

	GL_CHECK(glEnable(GL_DEPTH_TEST));
	
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
	GL_CHECK(glClearColor(r, g, b, a));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

