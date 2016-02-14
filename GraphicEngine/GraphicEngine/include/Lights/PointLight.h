#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "Lights/Light.h"

class PointLight : public Light
{
public:

private:

	float m_intensity;
	float m_distance;
	float m_decay;					// 


};

#endif