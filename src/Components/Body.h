#ifndef BODY_H
#define BODY_H

#include "Shaders/Shader.h"
#include "Textures/Texture.h"
#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"

class Body
{
private:
	VertexArray* _vao;
	VertexBuffer* _vbo;
	IndexBuffer* _ibo;
	Shader* _shader;
	Texture* _texture;
	
public:
	Body(VertexArray* vao, VertexBuffer* vbo, IndexBuffer* ibo, Shader* shader, Texture* texture);
	~Body();

	Body(const Body&) = delete;
	Body& operator=(const Body&) = delete;

	VertexArray* GetVAO() const { return _vao; }
	IndexBuffer* GetIBO() const { return _ibo; }
	Shader* GetShader() const { return _shader; }
	Texture* GetTexture() const { return _texture; }
};

class BodyBuilder
{
private:
	std::vector<float> _vertices{};
	std::vector<unsigned int> _indices{};
	VertexBufferLayout _layout;
	std::string_view _vertexPath{};
	std::string_view _fragmentPath{};
	std::string_view _texturePath{};

public:
	BodyBuilder& SetGeometry(const std::vector<float> vertices, const std::vector<unsigned int> indices, const VertexBufferLayout& layout);
	BodyBuilder& SetShader(std::string_view vertexPath, std::string_view fragmentPath);
	BodyBuilder& SetTexture(std::string_view texturePath);
	Body* Build();
};

#endif