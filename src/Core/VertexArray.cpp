#include "VertexArray.h"

#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GL_CHECK(glGenVertexArrays(1, &_vaoID));
}

VertexArray::~VertexArray()
{
	GL_CHECK(glDeleteVertexArrays(1, &_vaoID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GL_CHECK(glEnableVertexAttribArray(i));
		GL_CHECK(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GL_CHECK(glBindVertexArray(_vaoID));
}

void VertexArray::Unbind() const
{
	GL_CHECK(glBindVertexArray(0));
}