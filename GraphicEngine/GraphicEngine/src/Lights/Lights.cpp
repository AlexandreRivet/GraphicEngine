#include "Lights/Light.h"

Light::Light(const Color& color, Camera* c)
	: m_color(color),
	m_shadowCamera(c),
	m_isBlinn(true),
	m_intensity(0.7f),
	m_shininess(1.f),
	m_shadowMapWidth(1024),
	m_shadowMapHeight(1024),
	m_depthMapObjectsInit(false)
{
	castShadow(true);
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
	mCastShadow = withShadow;

	updateDepthMapObject();
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

Color Light::getColor() const
{
	return m_color;
}

bool Light::isBlinn() const
{
	return m_isBlinn;
}

float Light::getIntensity() const
{
	return m_intensity;
}

float Light::getShininess() const
{
	return m_shininess;
}

Matrix4 Light::getProjectionLight() const
{
	if (m_shadowCamera == nullptr)
		return Matrix4::IDENTITY;
	return m_shadowCamera->getProjectionMatrix();
}

uint Light::getShadowMapWidth() const
{
	return m_shadowMapWidth;
}

uint Light::getShadowMapHeight() const
{
	return m_shadowMapHeight;
}

GLuint Light::getDepthMapFBO() const
{
	return m_depthMapFBO;
}

GLuint Light::getDepthMapTexture() const
{
	return m_depthMapTexture;
}

void Light::updateDepthMapObject()
{
	// Le framebuffer et depth map déjà instanciée
	if (m_depthMapObjectsInit)
	{
		// TODO: faut les détruire

		m_depthMapObjectsInit = false;
	}
	else
	{
		// On crée la depth map
		glGenTextures(1, &m_depthMapTexture);
		glBindTexture(GL_TEXTURE_2D, m_depthMapTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, m_shadowMapWidth, m_shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

		// On crée le framebuffer
		glGenFramebuffers(1, &m_depthMapFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);

		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapTexture, 0);
		glDrawBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "kek sur le framebuffer" << std::endl;

		m_depthMapObjectsInit = true;
	}
}