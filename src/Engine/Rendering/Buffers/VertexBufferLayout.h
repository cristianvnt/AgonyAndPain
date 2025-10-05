#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>
#include <glad/glad.h>
#include <Engine/Utils/Logger.h>


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
		}

		GL_ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> _elements;
	unsigned int _stride;

public:
	VertexBufferLayout() : _stride(0) {}

	template<typename T>
	VertexBufferLayout& Push(unsigned int count)
	{
		if constexpr (std::is_same_v<T, float>)
		{
			_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}
		else if constexpr (std::is_same_v<T, unsigned int>)
		{
			_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}
		else if constexpr (std::is_same_v<T, unsigned char>)
		{
			_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}
		else
		{
			static_assert(false, "AAAAA ERROR: Unsuported type for VertexBufferLayout::Push\n");
		}

		return *this;
	}

	const std::vector<VertexBufferElement>& GetElements() const { return _elements; }
	unsigned int GetStride() const { return _stride; }
};

#endif