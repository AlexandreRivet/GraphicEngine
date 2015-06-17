#include "Math/Vector3.h"

Vector3::Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x(_x), y(_y), z(_z)
{
}

Vector3::Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z)
{
}

Vector3::~Vector3(void) {}

float Vector3::operator[] (uint i) const
{
	return *(&x + i);
}

float& Vector3::operator[] (uint i)
{
	return *(&x + i);
}

Vector3 Vector3::operator + (const Vector3& v) const
{
	return Vector3(
		x + v.x,
		y + v.y,
		z + v.z);
}

Vector3 Vector3::operator + (const float s) const
{
	return Vector3(
		y + s,
		y + s,
		z + s);
}

Vector3 Vector3::operator - (const Vector3& v) const
{
	return Vector3(
		x - v.x,
		y - v.y,
		z - v.z);
}

Vector3 Vector3::operator - (const float s) const
{
	return Vector3(
		x - s,
		y - s,
		z - s);
}

Vector3 Vector3::operator * (const Vector3& v) const
{
	return Vector3(
		x * v.x,
		y * v.y,
		z * v.z);
}

Vector3 Vector3::operator * (const float s) const
{
	return Vector3(
		x * s,
		y * s,
		z * s);
}

Vector3 Vector3::operator / (const Vector3& v) const
{
	if (v.x == 0 && v.y == 0) return Vector3::ZERO;
	return Vector3(
		x / v.x,
		y / v.y,
		z / v.z);
}

Vector3 Vector3::operator / (const float s) const
{
	if (s == 0) return Vector3::ZERO;
	return Vector3(
		x / s,
		y / s,
		z / s);
}

Vector3& Vector3::operator += (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator += (const float s)
{
	x += s;
	y += s;
	z += s;
	return *this;
}

Vector3& Vector3::operator -= (const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator -= (const float s)
{
	x -= s;
	y -= s;
	z -= s;
	return *this;
}

Vector3& Vector3::operator *= (const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3& Vector3::operator *= (const float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator /= (const Vector3& v)
{
	if (v.x == 0 || v.y == 0 || v.z == 0) return *this;
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

Vector3& Vector3::operator /= (const float s)
{
	if (s == 0) return *this;
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vector3& Vector3::operator = (const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

bool Vector3::operator == (const Vector3& v) const
{
	return ((x == v.x) && (y == v.y) && (z == v.z));
}

bool Vector3::operator != (const Vector3& v)const
{
	return !operator==(v);
}

bool Vector3::operator < (const Vector3& v) const
{
	return ((x < v.x) && (y < v.y) && (z < v.z));
}

bool Vector3::operator >(const Vector3& v) const
{
	return ((x > v.x) && (y > v.y) && (z > v.z));
}

std::ostream& operator << (std::ostream& os, const Vector3& v)
{
	os << "Vector3(" << v.x << "," << v.y << "," << v.y << ")";
	return os;
}

float Vector3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::squaredLength() const
{
	return x * x + y * y + z * z;
}

float Vector3::distance(const Vector3& v) const
{
	return (*this - v).length();
}

float Vector3::squaredDistance(const Vector3& v) const
{
	return (*this - v).squaredLength();
}

float Vector3::dotProduct(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

float Vector3::normalise()
{
	float len = length();

	if (len > 0.0f)
	{
		x /= len;
		y /= len;
		z /= len;
	}
	return len;
}

const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NEGATIVE_UNIT_X(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NEGATIVE_UNIT_Y(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::NEGATIVE_UNIT_Z(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::UNIT_SCALE(1.0f, 1.0f, 0.0f);