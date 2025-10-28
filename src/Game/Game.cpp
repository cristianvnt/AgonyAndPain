#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

#include "Game.h"
#include "Utils/Paths.h"

#include "glm/gtc/matrix_transform.hpp"

using namespace Settings;

Game::Game() : _isRunning{ false },
	_window{ nullptr }, _renderer{ nullptr },
	_camera{ nullptr }, _player{ nullptr }
{
	_window = new (std::nothrow) Window;
	_renderer = new (std::nothrow) Renderer;
	_camera = new (std::nothrow) Camera;

	if (!_window || !_renderer || !_camera)
	{
		delete _renderer;
		delete _camera;
		delete _window;
		return;
	}

	Initialize();
}

Game::~Game()
{
	for (Cube* cube : _cubes)
		delete cube;

	delete _player;

	delete _window;
	delete _renderer;
	delete _camera;
}

void Game::Initialize()
{
	std::cout << "Initializing game...\n";
	std::cout << "Title: " << TITLE << "\n";
	std::cout << "Resolution: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << "\n";
	std::cout << "Target FPS: " << RendererSettings::TARGET_FPS << "\n";

	if (!_window->Initialize())
	{
		std::cout << "NOOOOO ERROR: Failed to init window\n";
		return;
	}

	_renderer->Initialize();

	_mouseSensitivity = SENSITIVITY;

	for (int i = 0; i < GetPositions().size(); ++i)
	{
		Cube* cube = new Cube(
			BodyBuilder()
			.SetGeometry(GetVertices(), GetIndices(), GetLayout())
			.SetShader(Path::Shader::VERTEX, Path::Shader::FRAGMENT)
			.SetTexture(Path::Texture::CONTAINER)
			.Build(),
			new Movement(GetPositions()[i])
		);
		cube->SetAngle(20.f * i);
		_cubes.emplace_back(cube);
	}

	_player = new Player{
		BodyBuilder()
			.SetGeometry(GetVertices(), GetIndices(), GetLayout())
			.SetShader(Path::Shader::VERTEX_PLAYER, Path::Shader::FRAGMENT_PLAYER)
			.SetTexture(Path::Texture::FACE)
			.Build(),
		new Movement(glm::vec3{1.f, 1.f, 5.f})
	};
	_player->SetSpeed(10.f);

	glfwSetWindowUserPointer(_window->GetGLFWwindow(), this);
	glfwSetCursorPosCallback(_window->GetGLFWwindow(), [](GLFWwindow* window, double x, double y)
		{
			Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
			if (game && glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
				game->HandleMouseMove(x, y);
		});

	glfwSetScrollCallback(_window->GetGLFWwindow(), [](GLFWwindow* window, double x, double y)
		{
			Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
			if (game)
				game->HandleScroll(x, y);
		});

	// imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplGlfw_InitForOpenGL(_window->GetGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init();

	_isRunning = true;
	std::cout << "YIPPEEEEEEEE\n";
}

void Game::ProcessInput()
{
	_window->PollEvents();
	
	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
		_input.moveForward = true;
	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
		_input.moveBackward = true;
	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS)
		_input.moveLeft = true;
	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS)
		_input.moveRight = true;
	_player->ProcessInput(_input);
	_input.ResetStates();

	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		_isRunning = false;

	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_X) == GLFW_PRESS)
		GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_Z) == GLFW_PRESS)
		GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		_cursorJustDisabled = true;
		glfwSetInputMode(_window->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		_cursorJustDisabled = false;
		glfwSetInputMode(_window->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void Game::Update(double deltaTime)
{
	for (Cube* cube : _cubes)
	{
		cube->Update(static_cast<float>(deltaTime));
		cube->GetRenderData().shader->ReloadChanges(static_cast<float>(_renderer->DeltaTime()));
	}
	
	_player->Update(static_cast<float>(deltaTime));
	_player->GetRenderData().shader->ReloadChanges(static_cast<float>(_renderer->DeltaTime()));

	_camera->FollowTarget(_player->GetMovement()->GetPosition(), _player->GetFront(), _player->GetUp());
}

void Game::Render()
{
	float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);
	glm::mat4 proj = _camera->GetProjMatrix(aspectRatio);
	glm::mat4 view = _camera->GetViewMatrix();

	for (int i = 0; i < _cubes.size(); ++i)
	{
		_cubes[i]->SetModel(_cubes[i]->GetMovement()->GetPosition());
		float randomGreen = (glm::sin(static_cast<float>(glfwGetTime()))) + 0.3f * i;
		_renderer->DrawObject(_cubes[i]->GetRenderData(), view, proj, glm::vec4{ 0.8f, 0.5f, randomGreen, 1.f });
	}

	_renderer->DrawObject(_player->GetRenderData(), view, proj);
}

void Game::Run()
{
	timeBeginPeriod(1);
	while (_isRunning && !_window->ShouldClose())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ProcessInput();
		Update(_renderer->DeltaTime());

		_renderer->BeginFrame();
		Render();

		// imgui
		ImGui::Begin("BLABLABLA");
		ImGui::Text("Application average %.3lf ms/frame (%d FPS)", 1000.0 / _renderer->GetFPS(), _renderer->GetFPS());
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		_window->SwapBuffers();
		_renderer->EndFrame();
	}
	timeEndPeriod(1);
}

void Game::HandleMouseMove(double x, double y)
{
	static double lastX = x, lastY = y;
	if (_cursorJustDisabled)
	{
		lastX = x;
		lastY = y;
		_cursorJustDisabled = false;
		return;
	}

	double xOffset = x - lastX;
	double yOffset = lastY - y;
	lastX = x;
	lastY = y;

	_player->Rotate(static_cast<float>(xOffset) * _mouseSensitivity, static_cast<float>(yOffset) * _mouseSensitivity);
}

void Game::HandleScroll(double x, double y)
{
	_camera->Zoom(static_cast<float>(y));
}