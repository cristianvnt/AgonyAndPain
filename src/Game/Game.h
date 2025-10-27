#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include "Components/Textures/Texture.h"
#include "Actors/Camera.h"
#include "Actors/Player.h"

class Game
{
private:
	Window* _window{};
	Renderer* _renderer{};
	Camera* _camera{};
	Player* _player{};
	bool _isRunning{};

	bool _cursorJustDisabled{};
	float _mouseSensitivity{};

	// temporary
	VertexArray* _vao{};
	VertexBuffer* _vbo{};
	IndexBuffer* _ibo{};
	Shader* _shader{};
	Texture* _texture{};
	std::vector<glm::vec3> _cubePositions{};

	void Initialize();
	void ProcessInput();
	void Update(double deltaTime);
	void Render();

public:
	Game();
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Run();

	// handlers
	void HandleMouseMove(double x, double y);
	void HandleScroll(double x, double y);
};

#endif
