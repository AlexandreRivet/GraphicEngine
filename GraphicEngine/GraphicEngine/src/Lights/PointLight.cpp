#include "Lights/PointLight.h"

PointLight::PointLight(const std::string& name)
	: 
	Light(name),
	m_constant(1.0f),
	m_linear(0.09f),
	m_quadratic(0.032f)
{

}