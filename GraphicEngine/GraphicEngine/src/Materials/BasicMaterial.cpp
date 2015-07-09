#include "Materials/BasicMaterial.h"

BasicMaterial::BasicMaterial(const std::string& name, const Vector3& color)
	: Material(name),
	mColor(color)
{

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

	mShader->setUniform("color", mColor);

	mShader->unbind();
}