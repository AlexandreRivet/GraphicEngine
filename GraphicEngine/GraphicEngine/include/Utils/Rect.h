#ifndef _RECT_H_
#define _RECT_H_

#include "Math/Vector2.h"

template<typename T>
struct Rect
{
    T x;
    T y;
    T w;
    T h;
};

bool isInside(const Rect<float>& bounding, const Vector2& point);

#endif