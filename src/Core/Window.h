#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Managers/GameManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Window
{
private:
	GLFWwindow* _window;
	int _width;
	int _height;
	std::string _title;
	WindowModes::Type _windowMode;

public:
	Window(int width, int height, const std::string& title, WindowModes::Type wMode);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool Initialize();
	void SwapBuffers();
	void PollEvents();
	bool ShouldClose() const;
	void Clear(float r, float g, float b, float a);
	GLFWwindow* GetGLFWwindow() { return _window; }

	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
};

#endif
