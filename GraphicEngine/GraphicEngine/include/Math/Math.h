#ifndef _MATH_H_
#define _MATH_H_

#include <cmath>

namespace Math
{
    extern const float TWO_PI;

    bool FloatEqual(float a, float b, float tolerance)
    {
        if (fabs(b - a) <= tolerance)
            return true;
        else
            return false;
    }

    static inline bool isNaN(float f)
    {
        return f != f;
    }

    float UnitRandom();
}

#endif //_MATH_H_