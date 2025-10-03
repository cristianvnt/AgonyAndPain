#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#include "Game.h"
#include "Utils/Paths.h"

#include "glm/gtc/matrix_transform.hpp"

Game::Game(const std::string_view& filePath)
	: _window{ filePath }, _renderer{ filePath }, _isRunning{ false }
{
	Initialize();
}

void Game::Initialize()
{
	const RendererSettings& rendererSettings = _renderer.GetSettings();
	const WindowSettings& windowSettings = _window.GetSettings();

	std::cout << "Initializing game...\n";
	std::cout << "Title: " << windowSettings.title << "\n";
	std::cout << "Resolution: " << windowSettings.width << "x" << windowSettings.height << "\n";
	std::cout << "Target FPS: " << rendererSettings.targetFPS << "\n";
	std::cout << "Window Mode: " << WindowModes::ToString(windowSettings.windowMode) << "\n";

	if (!_window.Initialize())
	{
		std::cout << "NOOOOO ERROR: Failed to init window\n";
		return;
	}

	_renderer.Initialize();
	
	// temporary init
	float vertices[] =
	{
		 // pos				 //tex
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 0
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 1
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // 2
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // 3

		// front
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // 4
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // 5
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 6
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // 7

		// left
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 8
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // 9
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 10
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // 11

		// right
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 12
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // 13
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 14
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // 15

		 // bottom
		 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 16
		  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 17
		  0.5f, -0.5f,  0.5f, 1.0f, 1.0f, // 18
		 -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, // 19

		 // top
		 -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // 20
		  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, // 21
		  0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 22
		 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f  // 23
	};

	unsigned int indices[] =
	{
		0, 1, 2, 2, 3, 0, // back
		4, 5, 6, 6, 7, 4, // front
		8, 9, 10, 10, 11, 8, // left
		12, 13, 14, 14, 15, 12, // right
		16, 17, 18, 18, 19, 16, // bottom
		20, 21, 22, 22, 23, 20  // top
	};

	_cubePositions =
	{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	GL_CHECK(glEnable(GL_BLEND));
	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	_vao = std::make_unique<VertexArray>();
	_vbo = std::make_unique<VertexBuffer>(vertices, 24 * 5 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	_vao->AddBuffer(*_vbo, layout);

	_ibo = std::make_unique<IndexBuffer>(indices, 6 * 6);

	glm::mat4 proj = glm::perspective(glm::radians(60.f), (float)windowSettings.width / (float)windowSettings.height, 0.1f, 100.f);
	glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
	//glm::mat4 model = glm::rotate(glm::mat4(1.f), glm::radians(-50.f), glm::vec3(1.f, 1.f, 0.f));

	_mvp = proj * view;

	_shader = std::make_unique<Shader>(Path::Shader::VERTEX, Path::Shader::FRAGMENT);
	_shader->Bind();

	_texture = std::make_unique<Texture>(Path::Texture::CONTAINER);
	_texture->Bind();

	_shader->SetUniform1i("u_Texture", 0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplGlfw_InitForOpenGL(_window.GetGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init();

	_isRunning = true;
	std::cout << "YIPPEEEEEEEE\n";
}

void Game::ProcessInput()
{
	_window.PollEvents();

	if (glfwGetKey(_window.GetGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		_isRunning = false;

	if (glfwGetKey(_window.GetGLFWwindow(), GLFW_KEY_X) == GLFW_PRESS)
		GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

	if (glfwGetKey(_window.GetGLFWwindow(), GLFW_KEY_Z) == GLFW_PRESS)
		GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
}

void Game::Update(double deltaTime)
{

}

void Game::Render()
{
	_shader->Bind();
	for (int i = 0; i < 10; i++)
	{
		float randomGreen = (glm::sin(static_cast<float>(glfwGetTime()))) + 0.3f * i;
		glm::mat4 model = glm::translate(glm::mat4(1.f), _cubePositions[i]);
		float angle = 20.f * i;
		model = glm::rotate(model, glm::radians(angle), _cubePositions[i]);
		_shader->SetUniformVec4("someColor", glm::vec4{ 0.8f, 0.5f, randomGreen, 1.f });
		_shader->SetUniformMat4f("u_Proj", _mvp * model);
		_renderer.Draw(*_vao, *_ibo, *_shader);
	}
}

void Game::Run()
{
	timeBeginPeriod(1);
	while (_isRunning && !_window.ShouldClose())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ProcessInput();
		Update(_renderer.DeltaTime());

		_renderer.BeginFrame(_window);
		Render();

		// imgui
		ImGui::Begin("BLABLABLA");
		ImGui::Text("Application average %.3lf ms/frame (%d FPS)", 1000.0 / _renderer.GetFPS(), _renderer.GetFPS());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		_renderer.EndFrame(_window);
	}
	timeEndPeriod(1);
}
