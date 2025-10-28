#include "Body.h"

Body::Body(VertexArray* vao, VertexBuffer* vbo, IndexBuffer* ibo, Shader* shader, Texture* texture, const glm::vec4& color /*= glm::vec4{ 1.f }*/)
	: _vao{ vao }, _vbo{ vbo }, _ibo{ ibo }, _shader{ shader }, _texture{ texture }, _color{ color }
{
}

Body::~Body()
{
	delete _texture;
	delete _shader;
	delete _ibo;
	delete _vbo;
	delete _vao;
}

BodyBuilder& BodyBuilder::SetGeometry(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const VertexBufferLayout& layout)
{
	_vertices = vertices;
	_indices = indices;
	_layout = layout;
	return *this;
}

BodyBuilder& BodyBuilder::SetShader(std::string_view vertexPath, std::string_view fragmentPath)
{
	_vertexPath = vertexPath;
	_fragmentPath = fragmentPath;
	return *this;
}

BodyBuilder& BodyBuilder::SetTexture(std::string_view texturePath)
{
	_texturePath = texturePath;
	return *this;
}

BodyBuilder& BodyBuilder::SetColor(const glm::vec4& color /*= glm::vec4{ 1.f }*/)
{
	_color = color;
	return *this;
}

Body* BodyBuilder::Build()
{
	unsigned int vertexSize = static_cast<unsigned int>(_vertices.size() * sizeof(float));

	VertexArray* vao = new VertexArray{};
	VertexBuffer* vbo = new VertexBuffer{ _vertices.data(), vertexSize };

	vao->AddBuffer(*vbo, _layout);

	IndexBuffer* ibo = new IndexBuffer{ _indices.data(), static_cast<unsigned int>(_indices.size()) };

	Shader* shader = new Shader{ _vertexPath, _fragmentPath };
	Texture* texture = new Texture{ _texturePath };

	return new Body(vao, vbo, ibo, shader, texture, _color);
}
