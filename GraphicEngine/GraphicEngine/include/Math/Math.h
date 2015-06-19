#ifndef _MATH_H_
#define _MATH_H_

#include <cmath>
#include <algorithm>

namespace Math
{
    extern const float TWO_PI;
    extern const float HALF_PI;

    bool FloatEqual(float a, float b, float tolerance = std::numeric_limits<float>::epsilon())
    {
        if (fabs(b - a) <= tolerance)
            return true;
        else
            return false;
    }

    template<typename T>
    inline T Clamp(T value, T min, T max)
    {
        return std::min(max, std::max(value, min));
    }

    inline bool isNaN(float f)
    {
        return f != f;
    }

    inline float invSqrt(float v)
    {
        return 1.0f / sqrt(v);
    }

    float UnitRandom();
}

#endif //_MATH_H_