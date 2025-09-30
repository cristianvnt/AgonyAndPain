#ifndef TEXTURE_H
#define TEXTURE_H

#include "string"

class Texture
{
private:
	unsigned int _textureID;
	std::string _filePath;
	unsigned char* _localBuffer;
	int _width;
	int _height;
	int _bpp;

public:
	Texture(std::string_view path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};

#endif