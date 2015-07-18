#include "Math/Math.h"

#include <ctime>

namespace Math
{
    const float TWO_PI = static_cast<float>(M_PI) * 2.0f;
    const float HALF_PI = 0.5f * static_cast<float>(M_PI);

	bool FloatEqual(float a, float b, float tolerance)
	{
		if (fabs(b - a) <= tolerance)
			return true;
		else
			return false;
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

    float UnitRandom()
    {
		return float(rand()) / float(RAND_MAX);
    }
}