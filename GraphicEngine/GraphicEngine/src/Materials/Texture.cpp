#include "Materials/Texture.h"

#include "Utils/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
	: mWidth(0),
	mHeight(0),
	mHasImage(false),
	mFormat(GL_RGBA),
	mGlobalFormat(GL_RGBA),
	mGLuid(0),
	mGLunit(0),
	mIndex(0),
	mMinFilter(GL_LINEAR),
	mMagFilter(GL_LINEAR)
{

}

Texture::Texture(const std::string& filename, uint index)
	: mWidth(0),
	mHeight(0),
	mHasImage(false),
	mFormat(GL_RGBA),
	mGlobalFormat(GL_RGBA),
	mGLuid(0),
	mGLunit(unitFromIndex(index)),
	mIndex(index),
	mMinFilter(GL_NEAREST),
	mMagFilter(GL_LINEAR)
{
	load(filename);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mGLuid);
}

void Texture::load(const std::string& filename)
{
	int n; // lol fallait un n
	mData = stbi_load(filename.c_str(), &mWidth, &mHeight, &n, 4);
	if (mWidth != 0 && mHeight != 0)
	{
		mHasImage = true;
		init();
	}
}

bool Texture::hasImage() const
{
	return mHasImage;
}

void Texture::init()
{
	glActiveTexture(mGLunit);
	glGenTextures(1, &mGLuid);
	glBindTexture(GL_TEXTURE_2D, mGLuid);

	if (mHasImage)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mGlobalFormat, GL_UNSIGNED_BYTE, mData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{

	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);
}

void Texture::bind()
{
	glActiveTexture(mGLunit);
	glBindTexture(GL_TEXTURE_2D, mGLuid);
}

void Texture::resize(uint w, uint h)
{
    tools::unusedArg(w, h);
}

void Texture::setFilters(uint min, uint mag)
{
	mMinFilter = min;
	mMagFilter = mag;
}

int Texture::getWidth() const
{
	return mWidth;
}

int Texture::getHeight() const
{
	return mHeight;
}

GLuint Texture::unitFromIndex(uint index)
{
	switch (index)
	{
		case 1: return GL_TEXTURE1;
		case 2: return GL_TEXTURE2;
		case 3: return GL_TEXTURE3;
		case 4: return GL_TEXTURE4;
		case 5: return GL_TEXTURE5;
		case 6: return GL_TEXTURE6;
		case 7: return GL_TEXTURE7;
		case 8: return GL_TEXTURE8;
		case 9: return GL_TEXTURE9;
		default: return GL_TEXTURE0;
	}
}