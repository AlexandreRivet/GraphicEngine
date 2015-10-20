#include "Utils/Rect.h" 

bool isInside(const Rect<float>& bounding, const Vector2& point)
{
    return  point.x > bounding.x && point.x < bounding.x + bounding.w && 
            point.y > bounding.y && point.y < bounding.y + bounding.h;
}