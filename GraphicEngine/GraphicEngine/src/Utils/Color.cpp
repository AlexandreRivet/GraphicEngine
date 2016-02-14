#include "Utils/Color.h"

Color::Color(float red, float green, float blue, float alpha)
	: m_red(red),
	m_green(green),
	m_blue(blue),
	m_alpha(alpha)
{

}

Color::~Color()
{

}

// #FF00FF00 <= format
void Color::setHexa(int hexaColor)
{
	m_red = (hexaColor >> 24 & 255) / 255.f;
	m_green = (hexaColor >> 16 & 255) / 255.f;
	m_blue = (hexaColor >> 8 & 255) / 255.f;
	m_alpha = (hexaColor & 255) / 255.f;
}

void Color::setRGBA(float red, float green, float blue, float alpha)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
	m_alpha = alpha;
}

float Color::getRed() const
{
	return m_red;
}

float Color::getGreen() const
{
	return m_green;
}

float Color::getBlue() const
{
	return m_blue;
}

float Color::getAlpha() const
{
	return m_alpha;
}