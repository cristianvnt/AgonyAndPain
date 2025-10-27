#include "Texture.h"
#include "Utils/Logger.h"

#include "stb_image.h"

Texture::Texture(std::string_view path)
	: _textureID(0), _filePath(path), _localBuffer(nullptr), _width(0), _height(0), _bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	_localBuffer = stbi_load(_filePath.c_str(), &_width, &_height, &_bpp, 4);

	GL_CHECK(glGenTextures(1, &_textureID));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, _textureID));

	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

	if (_localBuffer)
		stbi_image_free(_localBuffer);
}

Texture::~Texture()
{
	GL_CHECK(glDeleteTextures(1, &_textureID));
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, _textureID));
}

void Texture::Unbind() const
{
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}