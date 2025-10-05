#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Engine/Settings/WindowSettings.h"

class Window
{
private:
	GLFWwindow* _window;
	WindowSettings _windowSettings;

public:
	Window(const WindowSettings& settings);	
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool Initialize();
	void SwapBuffers();
	void PollEvents();
	bool ShouldClose() const;

	GLFWwindow* GetGLFWwindow() const { return _window; }
	const WindowSettings& GetSettings() const { return _windowSettings; }
};

#endif
