#include "Window.h"

#include <iostream>

#include "Engine/Utils/Logger.h"

Window::Window(const WindowSettings& settings)
	: _window{ nullptr }, _windowSettings{ settings }
{
}

Window::~Window()
{
	if (_window)
		glfwDestroyWindow(_window);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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
	switch (_windowSettings.windowMode)
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

	_window = glfwCreateWindow(_windowSettings.width, _windowSettings.height, _windowSettings.title.c_str(), monitor, nullptr);
	if (!_window)
	{
		std::cout << "NOOOOO ERROR: GLFW window failed.\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "NOOOOO ERROR: GLAD failed to init.\n";
		return false;
	}
	
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