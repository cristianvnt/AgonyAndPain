#ifndef TERRAIN_H
#define TERRAIN_H

#include "Components/Body.h"
#include "Components/RenderData.h"

#include "glm/glm.hpp"

class Terrain
{
private:
	Body* _body{};
	glm::vec3 _position{};
	RenderData _renderData{};

public:
	Terrain(Body* body, const glm::vec3& pos);
	~Terrain();

	void Update(float deltaTime);

	Body* GetBody() const;
	const glm::vec3& GetPos() const;
	RenderData& GetRenderData();

private:
	void UpdateRenderData();
};

static const VertexBufferLayout GetTerrainLayout()
{
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	return layout;
}

static const std::vector<float> GetTerrainVertices()
{
	return {
		// pos				//tex
	   -0.5f, -0.5f, -0.5f, 0.f, 0.f, // 0
		0.5f, -0.5f, -0.5f, 1.f, 0.f, // 1
		0.5f,  0.5f, -0.5f, 1.f, 1.f, // 2
	   -0.5f,  0.5f, -0.5f, 0.f, 1.f, // 3
	};
};

static const std::vector<unsigned int> GetTerrainIndices()
{
	return {
		0, 1, 2, 2, 3, 0, // back
	};
};

#endif