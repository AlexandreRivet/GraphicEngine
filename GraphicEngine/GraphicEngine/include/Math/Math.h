#ifndef _MATH_H_
#define _MATH_H_

#include <cmath>
#include <algorithm>

#define M_PI 3.14159265358979323846

namespace Math
{
    extern const float TWO_PI;
    extern const float HALF_PI;

	bool FloatEqual(float a, float b, float tolerance = std::numeric_limits<float>::epsilon());

    template<typename T>
    inline T Clamp(T value, T min, T max)
    {
        return std::min<T>(max, std::max<T>(value, min));
    }

	inline bool isNaN(float f)
    {
        return f != f;
    }

	inline float invSqrt(float v)
    {
        return 1.0f / sqrt(v);
    }

	inline float Sqr(float v)
    {
        return v * v;
    }

	inline float degToRad(float d)
    {
        return d * static_cast<float>(M_PI) / 180.0f;
    }

	inline float radToDeg(float r)
    {
        return r * 180.0f / static_cast<float>(M_PI);
    }

	inline float truncate(float r, int precision)
	{
		int value_10 = pow(10, precision);
		int y = value_10 * r;
		float result = (float)y / value_10;
		return result;
	}

    float UnitRandom();
}

#endif //_MATH_H_