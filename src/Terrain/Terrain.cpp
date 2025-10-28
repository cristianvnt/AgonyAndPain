#include "Terrain.h"

#include "glm/ext/matrix_transform.hpp"

#include "Utils/Settings.h"

using namespace SETTINGS;

Terrain::Terrain(Body* body, const glm::vec3& pos)
	: _body{ body }, _position{ pos }
{
}

Terrain::~Terrain()
{
	delete _body;
}

void Terrain::Update(float deltaTime)
{
	UpdateRenderData();
}

const glm::vec3& Terrain::GetPos() const
{
	return _position;
}

RenderData& Terrain::GetRenderData()
{
	return _renderData;
}

void Terrain::UpdateRenderData()
{
	glm::mat4 model = glm::translate(glm::mat4(1.f), _position);
	model = glm::rotate(model, glm::radians(TERRAIN::ANGLE), glm::vec3{ 1.f, 0.f, 0.f });
	model = glm::scale(model, glm::vec3{ 50.f, 50.f, 0.f });

	_renderData.model = model;
	_renderData.vao = _body->GetVAO();
	_renderData.ibo = _body->GetIBO();
	_renderData.shader = _body->GetShader();
	_renderData.texture = _body->GetTexture();
	_renderData.color = _body->GetColor();
}