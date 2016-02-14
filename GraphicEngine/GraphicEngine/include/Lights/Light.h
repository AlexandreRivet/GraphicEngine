#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Objects/Object3D.h"
#include "Utils/Color.h"
#include "Cameras/PerspectiveCamera.h"
#include "Cameras/OrthographicCamera.h"

class Light : public Object3D
{
public:

	Light(const Color& color, Camera* = nullptr);
	~Light();

	void setColor(Color& c);
	
	void castShadow(bool withShadow);
	void setShadowCamera(Camera* c);
	void setShadowBias(float value);
	void setShadowMapWidth(float width);
	void setShadowMapHeight(float height);

protected:

	Color m_color;

	// For shadows
	bool m_castShadow;
	Camera* m_shadowCamera;
	float m_shadowBias;
	float m_shadowMapWidth;
	float m_shadowMapHeight;
};

#endif