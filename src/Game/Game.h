#ifndef GAME_H
#define GAME_H

#include "Engine/Rendering/Renderer.h"
#include "Engine/Rendering/Textures/Texture.h"
#include "Engine/Settings/GameSettings.h"
#include "Engine/Rendering/Camera.h"
#include "Entities/Player.h"

class Game
{
private:
	Window* _window;
	Renderer* _renderer;
	Camera* _camera;
	Player* _player;
	bool _isRunning;
	bool _isFirstPerson;

	float _mouseSensitivity{};
	float _moveSpeed{};

	// temporary
	VertexArray* _vao;
	VertexBuffer* _vbo;
	IndexBuffer* _ibo;
	Shader* _shader;
	Texture* _texture;
	std::vector<glm::vec3> _cubePositions;

	void Initialize();
	void ProcessInput();
	void Update(double deltaTime);
	void Render();

public:
	Game(const std::string_view& configPath);
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Run();

	// handlers
	void HandleMouseMove(double x, double y);
	void HandleScroll(double x, double y);
};

#endif
