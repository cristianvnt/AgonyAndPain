#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include "Components/Textures/Texture.h"
#include "Actors/Camera.h"
#include "Actors/Player.h"
#include "Actors/Cube.h"

class Game
{
private:
	Window* _window{};
	Renderer* _renderer{};
	Camera* _camera{};
	Player* _player{};
	std::vector<Cube*> _cubes{};

	InputState _input{};

	bool _isRunning{};

	bool _cursorJustDisabled{};
	float _mouseSensitivity{};

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
