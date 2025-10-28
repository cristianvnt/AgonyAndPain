#include "Window.h"

#include <iostream>

#include "Utils/Logger.h"
#include "Utils/Settings.h"

using namespace SETTINGS;

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

	_window = glfwCreateWindow(GAME::SCREEN_WIDTH, GAME::SCREEN_HEIGHT, GAME::TITLE, nullptr, nullptr);
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