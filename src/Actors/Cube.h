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

	void UpdateRenderData();
public:
	Cube(Body* body, Movement* movement);
	~Cube();

	void Update(float deltaTime);

	Cube& SetAngle(float angle);
	Cube& SetModel(const glm::vec3& pos);

	RenderData& GetRenderData();
	Movement* GetMovement();
};

static const VertexBufferLayout GetLayout()
{
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	return layout;
}

static const std::vector<float> GetVertices()
{
	return {
		// pos				 //tex
	   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 0
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 1
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // 2
	   -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // 3

	   // front
	   -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // 4
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // 5
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 6
	   -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // 7

	   // left
	   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 8
	   -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // 9
	   -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 10
	   -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // 11

	   // right
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 12
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // 13
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 14
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // 15

		// bottom
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 16
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 17
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, // 18
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, // 19

		// top
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // 20
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, // 21
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 22
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f  // 23
	};
};

static const std::vector<glm::vec3> GetPositions()
{
	return {
		glm::vec3(0.0f,  0.0f,  -1.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
};

static const std::vector<unsigned int> GetIndices()
{
	return {
		0, 1, 2, 2, 3, 0, // back
		4, 5, 6, 6, 7, 4, // front
		8, 9, 10, 10, 11, 8, // left
		12, 13, 14, 14, 15, 12, // right
		16, 17, 18, 18, 19, 16, // bottom
		20, 21, 22, 22, 23, 20  // top
	};
};

#endif CUBE_H