#include "VertexBuffer.h"

#include "Utils/Logger.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GL_CHECK(glGenBuffers(1, &_vboID));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _vboID));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GL_CHECK(glDeleteBuffers(1, &_vboID));
}

void VertexBuffer::Bind() const
{
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _vboID));
}

void VertexBuffer::Unbind() const
{
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}