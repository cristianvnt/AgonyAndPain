#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#include "Game.h"
#include "Engine/Utils/Paths.h"

#include "glm/gtc/matrix_transform.hpp"

Game::Game(const std::string_view& configPath)
	: _isRunning{ false }, _player{ nullptr },
	_vao{ nullptr }, _vbo{ nullptr }, _ibo{ nullptr },
	_shader{ nullptr }, _texture{ nullptr }
{
	GameSettings settings = GameSettings::FromConfig(configPath);
	_window = new (std::nothrow) Window{ settings.window };
	_renderer = new (std::nothrow) Renderer{ settings.renderer };
	_camera = new (std::nothrow) Camera{ settings.camera };

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
	delete _texture;
	delete _shader;
	delete _ibo;
	delete _vbo;
	delete _vao;
	delete _player;

	delete _window;
	delete _renderer;
	delete _camera;
}

void Game::Initialize()
{
	std::cout << "Initializing game...\n";
	std::cout << "Title: " << _window->GetSettings().title << "\n";
	std::cout << "Resolution: " << _window->GetSettings().width << "x" << _window->GetSettings().height << "\n";
	std::cout << "Target FPS: " << _renderer->GetSettings().targetFPS << "\n";
	std::cout << "Window Mode: " << WindowModes::ToString(_window->GetSettings().windowMode) << "\n";

	if (!_window->Initialize())
	{
		std::cout << "NOOOOO ERROR: Failed to init window\n";
		return;
	}

	_renderer->Initialize();

	_mouseSensitivity = _camera->GetSettings().sensitivity;
	
	// temporary init
	std::vector<float> vertices =
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

	std::vector<unsigned int> indices =
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
		glm::vec3(0.0f,  0.0f,  -1.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	_vao = new VertexArray{};
	_vbo = new VertexBuffer{ vertices.data(), 24 * 5 * sizeof(float)};

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	_vao->AddBuffer(*_vbo, layout);

	_ibo = new IndexBuffer{ indices.data(), 6 * 6};

	_shader = new Shader{ Path::Shader::VERTEX, Path::Shader::FRAGMENT };
	_shader->Bind();

	_texture = new Texture{ Path::Texture::CONTAINER };
	_texture->Bind();
	_shader->SetUniform1i("u_Texture", 0);

	_player = new Player{
		BodyBuilder()
			.SetGeometry(vertices, indices, layout)
			.SetShader(Path::Shader::VERTEX_PLAYER, Path::Shader::FRAGMENT_PLAYER)
			.SetTexture(Path::Texture::FACE)
			.Build()
	};
	_player->SetSpeed(5.f);

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
	_player->ProcessInput(_window);

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
	_shader->ReloadChanges(static_cast<float>(_renderer->DeltaTime()));

	_player->Update(static_cast<float>(deltaTime));

	_camera->FollowTarget(_player->GetPosition(), _player->GetFront(), _player->GetUp());
}

void Game::Render()
{
	float aspectRatio = (float)_window->GetSettings().width / (float)_window->GetSettings().height;
	glm::mat4 proj = _camera->GetProjMatrix(aspectRatio);
	glm::mat4 view = _camera->GetViewMatrix();

	_shader->Bind();
	_texture->Bind();
	for (int i = 0; i < _cubePositions.size(); i++)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.f), _cubePositions[i]);
		float angle = 20.f * i;
		model = glm::rotate(model, glm::radians(angle), _cubePositions[i]);

		float randomGreen = (glm::sin(static_cast<float>(glfwGetTime()))) + 0.3f * i;
		_shader->SetUniformVec4("someColor", glm::vec4{ 0.8f, 0.5f, randomGreen, 1.f });
		_shader->SetUniformMat4f("u_Proj", proj);
		_shader->SetUniformMat4f("u_View", view);
		_shader->SetUniformMat4f("u_Model", model);
		_renderer->Draw(*_vao, *_ibo, *_shader);
	}

	_player->Render(*_renderer, view, proj);
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

		_renderer->BeginFrame(_window);
		Render();

		// imgui
		ImGui::Begin("BLABLABLA");
		ImGui::Text("Application average %.3lf ms/frame (%d FPS)", 1000.0 / _renderer->GetFPS(), _renderer->GetFPS());
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		_renderer->EndFrame(_window);
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

	_player->Rotate(xOffset * _mouseSensitivity, yOffset * _mouseSensitivity);
}

void Game::HandleScroll(double x, double y)
{
	_camera->Zoom(static_cast<float>(y));
}