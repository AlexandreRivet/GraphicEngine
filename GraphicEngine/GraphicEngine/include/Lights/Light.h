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
	uint getShadowMapWidth() const;
	uint getShadowMapHeight() const;
	GLuint getDepthMapFBO() const;
	GLuint getDepthMapTexture() const;

	Color getColor() const;
	bool isBlinn() const;
	float getIntensity() const;
	float getShininess() const;
	Matrix4 getProjectionLight() const;

	void updateDepthMapObject();


protected:

	Color m_color;
	bool m_isBlinn;
	float m_intensity;
	float m_shininess;

	// For shadows
	Camera* m_shadowCamera;
	float m_shadowBias;
	uint m_shadowMapWidth;
	uint m_shadowMapHeight;

	bool m_depthMapObjectsInit;
	GLuint m_depthMapFBO;
	GLuint m_depthMapTexture;
};

#endif