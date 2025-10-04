#ifndef GAME_H
#define GAME_H

#include "Rendering/Renderer.h"
#include "Rendering/Textures/Texture.h"
#include "Settings/GameSettings.h"
#include "Rendering/Camera.h"

class Game
{
private:
	Window* _window;
	Renderer* _renderer;
	Camera* _camera;
	bool _isRunning;

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
