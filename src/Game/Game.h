#ifndef GAME_H
#define GAME_H

#include "Rendering/Renderer.h"
#include "Rendering/Textures/Texture.h"

class Game
{
private:
	Window _window;
	Renderer _renderer;
	bool _isRunning;

	// temporary
	std::unique_ptr<VertexArray> _vao;
	std::unique_ptr<VertexBuffer> _vbo;
	std::unique_ptr<IndexBuffer> _ibo;
	std::unique_ptr<Shader> _shader;
	std::unique_ptr<Texture> _texture;
	std::vector<glm::vec3> _cubePositions;
	glm::mat4 _mvp{};

	void Initialize();
	void ProcessInput();
	void Update(double deltaTime);
	void Render();

public:
	Game(const std::string_view& filePath);
	void Run();
};

#endif
