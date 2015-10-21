#ifndef _STRUCTS_H_
#define _STRUCTS_H_

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color(float _r, float _g, float _b, float _a)
		: r(_r),
		g(_g),
		b(_b),
		a(_a)
	{}
};

#endif