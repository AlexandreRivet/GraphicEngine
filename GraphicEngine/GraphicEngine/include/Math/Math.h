#ifndef _MATH_H_
#define _MATH_H_

namespace Math
{
    bool FloatEqual(float a, float b, float tolerance)
    {
        if (fabs(b - a) <= tolerance)
            return true;
        else
            return false;
    }
}

#endif //_MATH_H_