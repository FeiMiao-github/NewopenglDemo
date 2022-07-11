#include <stdlib.h>
#include <stb/stb_image.h>

#include "demo/loader.h"
#include "demo/texture.h"

static void LoadTextureData(const std::string& img)
{
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(GetTextureFullPath(img).c_str(), &width, &height, &nrChannel, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
        throw TextureLoadException(img);
	}

	stbi_image_free(data);
}

Texture::Texture(const std::string& name)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	LoadTextureData(name.c_str());
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::Use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}
