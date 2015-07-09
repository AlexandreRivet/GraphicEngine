#include "Math/Math.h"

#include <ctime>

namespace Math
{
    static const float TWO_PI = static_cast<float>(M_PI) * 2.0f;
    static const float HALF_PI = 0.5f * static_cast<float>(M_PI);

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

    float UnitRandom()
    {
		return float(rand()) / float(RAND_MAX);
    }
}