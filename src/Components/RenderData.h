#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"
#include "Textures/Texture.h"
#include "Shaders/Shader.h"

struct RenderData
{
	glm::mat4 model{};
	VertexArray* vao{};
	IndexBuffer* ibo{};
	Shader* shader{};
	Texture* texture{};
	glm::vec4 color{};
};

#endif