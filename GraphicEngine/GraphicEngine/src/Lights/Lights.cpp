#include "Lights/Light.h"

Light::Light(const Color& color, Camera* c)
	: m_color(color),
	m_shadowCamera(c)
{

}

Light::~Light()
{

}

void Light::setColor(Color& c)
{
	m_color = c;
}

void Light::castShadow(bool withShadow)
{
	m_castShadow = withShadow;
}

void Light::setShadowCamera(Camera* c)
{
	m_shadowCamera = c;
}

void Light::setShadowBias(float value)
{
	m_shadowBias = value;
}

void Light::setShadowMapWidth(float width)
{
	m_shadowMapWidth = width;
}

void Light::setShadowMapHeight(float height)
{
	m_shadowMapHeight = height;
}