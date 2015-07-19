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

    float UnitRandom()
    {
		return float(rand()) / float(RAND_MAX);
    }
}