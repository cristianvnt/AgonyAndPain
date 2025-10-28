#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Window
{
private:
	GLFWwindow* _window{};

public:
	Window() : _window{ nullptr } {}
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool Initialize();
	void SwapBuffers();
	void PollEvents();
	bool ShouldClose() const;

	GLFWwindow* GetGLFWwindow() const { return _window; }
};

#endif
