#include "Lights/Light.h"

Light::Light(const std::string& name)
	: 
	Object3D(name),
	m_ambient(Color(0.05f, 0.05f, 0.05f)),
	m_diffuse(Color(0.5f, 0.5f, 0.5f)),
	m_specular(Color(0.6f, 0.6f, 0.6f)),
	m_shadowCamera(nullptr),
	m_shadowMapWidth(1024),
	m_shadowMapHeight(1024),
	m_depthMapObjectsInit(false)
{
	castShadow(true);
}

Light::~Light()
{

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
		glDeleteTextures(1, &m_depthMapTexture);
		glDeleteFramebuffers(1, &m_depthMapFBO);

		m_depthMapObjectsInit = false;
	}
	else
	{
		glGenFramebuffers(1, &m_depthMapFBO);

		// On crée la depth map
		glGenTextures(1, &m_depthMapTexture);
		glBindTexture(GL_TEXTURE_2D, m_depthMapTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_shadowMapWidth, m_shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_CLAMP_TO_BORDER);
		static GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		// On crée le framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapTexture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "kek sur le framebuffer" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_depthMapObjectsInit = true;
	}
}