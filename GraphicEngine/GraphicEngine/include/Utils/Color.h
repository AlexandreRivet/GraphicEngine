#ifndef _COLOR_H_
#define _COLOR_H_

#include "prerequisites.h"

class Color
{
public:
	
	Color(float red = 1.f, float green = 1.f, float blue = 1.f, float alpha = 1.f);
	~Color();

	void setHexa(int hecaColor); // ?
	void setRGBA(float red, float green, float blue, float alpha);

	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;



private:

	float m_red;
	float m_green;
	float m_blue;
	float m_alpha;
};


#endif