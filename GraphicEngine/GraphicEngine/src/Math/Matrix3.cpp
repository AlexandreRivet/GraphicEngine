#include "Math/Matrix3.h"

Matrix3::Matrix3(const float* data = nullptr)
{
	if (data == nullptr)
	{
		*this = identity();
	}
	else
	{
		memcpy(m_data, data, 9 * sizeof(float));
	}
}

Matrix3::Matrix3(const Matrix3& other)
{
	memcpy(m_data, other.m_data, 9 * sizeof(float));
}

Matrix3::~Matrix3()
{

}

float Matrix3::getValue(uint iRow, uint iCol) const
{
	assert(iRow <3 && iCol < 3);

	return m_data[iRow * 3 + iCol];
}