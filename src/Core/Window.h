#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Window
{
private:
	GLFWwindow* _window;
	int _width;
	int _height;
	std::string _title;

public:
	Window(int width, int height, const std::string& title);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool Initialize();
	void SwapBuffers();
	void PollEvents();
	bool ShouldClose() const;
	void Clear(float r, float g, float b, float a);
	GLFWwindow* GetGLFWwindow() { return _window; }
};

#endif
