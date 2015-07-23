#include "Materials/BasicMaterial.h"

BasicMaterial::BasicMaterial(const std::string& name, const Vector3& color, const std::string& textureFilename)
	: Material(name),
	mColor(color),
	mHasTexture(false),
	mTexture(textureFilename)
{
	mHasTexture = mTexture.hasImage();
}

void BasicMaterial::setColor(const Vector3& color)
{
	mColor = color;
}

Vector3& BasicMaterial::getColor()
{
	return mColor;
}

void BasicMaterial::bind()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	mShader->bind();

	mShader->setUniform("u_color", mColor);

	if (mHasTexture)
	{
		mTexture.bind();
		mShader->setUniform("u_sampler", mTexture);
	}
	
}

void BasicMaterial::unbind()
{
	mShader->unbind();
}

void BasicMaterial::setTexture(Texture t)
{
	mTexture = t;
	mHasTexture = true;
}