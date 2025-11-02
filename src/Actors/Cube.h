#ifndef CUBE_H
#define CUBE_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Components/RenderData.h"
#include "Components/Body.h"
#include "Components/Movement.h"

class Cube
{
private:
	Body* _body{};
	Movement* _movement{};
	float _angle{};
	RenderData _renderData{};

public:
	Cube(Body* body, Movement* movement);
	~Cube();

	void Update(float deltaTime);

	Cube& SetAngle(float angle);
	Cube& SetModel(const glm::vec3& axis);
	Cube& SetColor(const glm::vec4& col);

	RenderData& GetRenderData();
	Movement* GetMovement();

private:
	void UpdateRenderData();
};

static const VertexBufferLayout GetLayout()
{
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	return layout;
}

#endif CUBE_H