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
	mMinFilter(GL_LINEAR),
	mMagFilter(GL_LINEAR)
{

}

Texture::Texture(const std::string& filename)
	: mWidth(0),
	mHeight(0),
	mHasImage(false),
	mFormat(GL_RGBA),
	mGlobalFormat(GL_RGBA),
	mGLuid(0),
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

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::resize(uint w, uint h)
{
    tools::unusedArg(w, h);
}

void Texture::setFilters(uint min, uint mag)
{
	mMinFilter = min;
	mMagFilter = mag;

	glBindTexture(GL_TEXTURE_2D, mGLuid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getWidth() const
{
	return mWidth;
}

int Texture::getHeight() const
{
	return mHeight;
}