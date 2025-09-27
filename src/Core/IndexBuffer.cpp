#include "IndexBuffer.h"

#include "Utils/Logger.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
	: _count(count)
{
	GL_CHECK(glGenBuffers(1, &_bufferID));
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID));
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GL_CHECK(glDeleteBuffers(1, &_bufferID));
}

void IndexBuffer::Bind() const
{
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID));
}

void IndexBuffer::Unbind() const
{
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}