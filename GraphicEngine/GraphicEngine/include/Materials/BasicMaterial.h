#ifndef _BASICMATERiAL_H_
#define _BASICMATERiAL_H_

#include "Materials/Material.h"
#include "Math/Vector3.h"

class BasicMaterial : public Material
{
public:

	BasicMaterial(const std::string& name, const Vector3& color = Vector3(), const std::string& textureFilename = std::string());

	void setColor(const Vector3& color);
	Vector3& getColor();

	void setTexture(Texture t);

	void bind();
	void unbind();

protected:

	Vector3 mColor;
	Texture mTexture;

	bool mHasTexture;

};

#endif