#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer
{
private:
	unsigned int _vboID{};
	unsigned int _size{};

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetSize() const { return _size; }
};

#endif