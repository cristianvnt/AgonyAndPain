#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer
{
private:
	unsigned int _bufferID;

public:
	VertexBuffer(const void* data, size_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

#endif