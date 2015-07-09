#ifndef _MATH_H_
#define _MATH_H_

#include <cmath>
#include <algorithm>

namespace Math
{
    extern const float TWO_PI;
    extern const float HALF_PI;

	bool FloatEqual(float a, float b, float tolerance = std::numeric_limits<float>::epsilon());

    template<typename T>
    inline T Clamp(T value, T min, T max)
    {
        return std::min(max, std::max(value, min));
    }

	inline bool isNaN(float f);

	inline float invSqrt(float v);

	inline float Sqr(float v);

    float UnitRandom();
}

#endif //_MATH_H_