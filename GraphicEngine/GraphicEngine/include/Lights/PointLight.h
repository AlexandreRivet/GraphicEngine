#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "Lights/Light.h"

class PointLight : public Light
{
public:

	PointLight(const std::string& name);

	float m_constant;
	float m_linear;
	float m_quadratic;

private: 

};

#endif