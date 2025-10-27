#include "Cube.h"

Cube::Cube(Body* body, Movement* movement)
	: _body{ body }, _movement{ movement }
{
}

Cube::~Cube()
{
	delete _movement;
	delete _body;
}

void Cube::Update(float deltaTime)
{
	UpdateRenderData();
}

Cube& Cube::SetAngle(float angle)
{
	_angle = angle;
	return *this;
}

Cube& Cube::SetModel(const glm::vec3& pos)
{
	_renderData.model = glm::rotate(_renderData.model, glm::radians(_angle), pos);
	return *this;
}

RenderData& Cube::GetRenderData()
{
	return _renderData;
}

Movement* Cube::GetMovement()
{
	return _movement;
}

void Cube::UpdateRenderData()
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), _movement->GetPosition());

	_renderData.model = m;
	_renderData.vao = _body->GetVAO();
	_renderData.ibo = _body->GetIBO();
	_renderData.shader = _body->GetShader();
	_renderData.texture = _body->GetTexture();
}

