#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

#include "Game.h"
#include "Utils/Paths.h"
#include "Utils/Settings.h"
#include "Utils/Utils.h"

#include "glm/gtc/matrix_transform.hpp"

using namespace SETTINGS;

Game::Game() : _isRunning{ false },
_window{ nullptr }, _renderer{ nullptr },
_camera{ nullptr }, _player{ nullptr },
_terrain{ nullptr }
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
	delete _terrain;
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
	std::cout << "Title: " << GAME::TITLE << "\n";
	std::cout << "Resolution: " << GAME::SCREEN_WIDTH << "x" << GAME::SCREEN_HEIGHT << "\n";
	std::cout << "Target FPS: " << RENDERER::TARGET_FPS << "\n";

	if (!_window->Initialize())
	{
		std::cout << "NOOOOO ERROR: Failed to init window\n";
		return;
	}

	_renderer->Initialize();

	_mouseSensitivity = SENSITIVITY;

	_terrain = new Terrain(
		BodyBuilder()
		.SetGeometry(GetTerrainVertices(), GetTerrainIndices(), GetLayout())
		.SetShader(Path::Shader::VERTEX_TERRAIN, Path::Shader::FRAGMENT_TERRAIN)
		.SetColor(glm::vec4{ 0.5f, 0.5f, 0.5f, 1.f })
		.Build(),
		TERRAIN::POSITION
	);

	std::vector<glm::vec3> cubePositions = Utils::Cube::GetPositions();
	std::vector<float> cubeVertices = Utils::Cube::GetVertices();
	std::vector<unsigned int> cubeIndices = Utils::Cube::GetIndices();

	for (int i = 0; i < cubePositions.size(); ++i)
	{
		Cube* cube = new Cube(
			BodyBuilder()
			.SetGeometry(cubeVertices, cubeIndices, GetLayout())
			.SetShader(Path::Shader::VERTEX, Path::Shader::FRAGMENT)
			.SetTexture(Path::Texture::CONTAINER)
			.Build(),
			new Movement(cubePositions[i])
		);
		cube->SetAngle(20.f * i);
		_cubes.emplace_back(cube);
	}

	_player = new Player{
		BodyBuilder()
			.SetGeometry(cubeVertices, cubeIndices, GetLayout())
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

	_isRunning = true;
	std::cout << "YIPPEEEEEEEE\n";
}

void Game::ProcessInput(bool isCollision)
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
	if (glfwGetKey(_window->GetGLFWwindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		_input.moveUpward = true;

	_player->SetCollision(CheckCollision());
	_player->ProcessInput(_input);

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
	_terrain->Update(static_cast<float>(deltaTime));
	_terrain->GetRenderData().shader->ReloadChanges(static_cast<float>(deltaTime));

	for (Cube* cube : _cubes)
	{
		cube->Update(static_cast<float>(deltaTime));
		cube->GetRenderData().shader->ReloadChanges(static_cast<float>(deltaTime));
	}

	_player->Update(_input, static_cast<float>(deltaTime));
	_input.ResetStates();
	_player->GetRenderData().shader->ReloadChanges(static_cast<float>(deltaTime));

	_camera->FollowTarget(_player->GetMovement()->GetPosition(), _player->GetFront(), _player->GetUp());
}

void Game::Render()
{
	float aspectRatio = static_cast<float>(GAME::SCREEN_WIDTH) / static_cast<float>(GAME::SCREEN_HEIGHT);
	glm::mat4 proj = _camera->GetProjMatrix(aspectRatio);
	glm::mat4 view = _camera->GetViewMatrix();

	_renderer->DrawObject(_terrain->GetRenderData(), view, proj);

	for (int i = 0; i < _cubes.size(); ++i)
	{
		float randomGreen = (glm::sin(static_cast<float>(glfwGetTime()))) + 0.3f * i;
		_cubes[i]->SetColor(glm::vec4{ 0.8f, 0.5f, randomGreen, 1.f }).SetModel(_cubes[i]->GetMovement()->GetPosition());
		_renderer->DrawObject(_cubes[i]->GetRenderData(), view, proj);
	}

	_renderer->DrawObject(_player->GetRenderData(), view, proj);
}

void Game::Run()
{
	timeBeginPeriod(1);
	while (_isRunning && !_window->ShouldClose())
	{
		ProcessInput(CheckCollision());
		Update(_renderer->DeltaTime());

		_renderer->BeginFrame();
		Render();

		_window->SwapBuffers();
		_renderer->EndFrame();
	}
	timeEndPeriod(1);
}

bool Game::CheckCollision()
{
	return _player->GetPosition().y >= _terrain->GetPos().y && _player->GetPosition().y <= _terrain->GetPos().y + 0.7f &&
		_player->GetPosition().x <= 25.f && _player->GetPosition().x >= -25.f && _player->GetPosition().z >= -25.f && _player->GetPosition().z <= 25.f;
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