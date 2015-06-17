#include "Math/Vector2.h"

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{
}

Vector2::Vector2(const Vector2& v) : x(v.x), y(v.y)
{
}

Vector2::~Vector2(void) {}

Vector2 Vector2::operator + (const Vector2& v) const
{
	return Vector2(
		x + v.x,
		y + v.y);
}

Vector2 Vector2::operator + (const float s) const
{
	return Vector2(
		y + s,
		y + s);
}

Vector2 Vector2::operator - (const Vector2& v) const
{
	return Vector2(
		x - v.x,
		y - v.y);
}

Vector2 Vector2::operator - (const float s) const
{
	return Vector2(
		x - s,
		y - s);
}

Vector2 Vector2::operator * (const Vector2& v) const
{
	return Vector2(
		x * v.x,
		y * v.y);
}

Vector2 Vector2::operator * (const float s) const
{
	return Vector2(
		x * s,
		y * s);
}

Vector2 Vector2::operator / (const Vector2& v) const
{
	if (v.x == 0 && v.y == 0) return Vector2::ZERO;
	return Vector2(
		x / v.x,
		y / v.y);
}

Vector2 Vector2::operator / (const float s) const
{
	if (s == 0) return Vector2::ZERO;
	return Vector2(
		x / s,
		y / s);
}

Vector2& Vector2::operator += (const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator += (const float s)
{
	x += s;
	y += s;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator -= (const float s)
{
	x -= s;
	y -= s;
	return *this;
}

Vector2& Vector2::operator *= (const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2& Vector2::operator *= (const float s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator /= (const Vector2& v)
{
	if (v.x == 0 && v.y == 0) return *this;
	x /= v.x;
	y /= v.y;
	return *this;
}

Vector2& Vector2::operator /= (const float s)
{
	if (s == 0) return *this;
	x /= s;
	y /= s;
	return *this;
}

Vector2& Vector2::operator = (const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

bool Vector2::operator == (const Vector2& v) const
{
	return ((x == v.x) && (y == v.y));
}

bool Vector2::operator != (const Vector2& v)const
{
	return ((x != v.x) || (y != v.y));
}

bool Vector2::operator < (const Vector2& v) const
{
	return ((x < v.x) && (y < v.y));
}

bool Vector2::operator >(const Vector2& v) const
{
	return ((x > v.x) && (y > v.y));
}

std::ostream& operator << (std::ostream& os, const Vector2& v)
{
	os << "Vector2(" << v.x << "," << v.y << ")";
	return os;
}

float Vector2::length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::squaredLength() const
{
	return x * x + y * y;
}

float Vector2::distance(const Vector2& v) const
{
	return (*this - v).length();
}

float Vector2::squaredDistance(const Vector2& v) const
{
	return (*this - v).squaredLength();
}

float Vector2::dotProduct(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

float Vector2::crossProduct(const Vector2& v) const
{
	return x * v.y - v.x * y;
}

float Vector2::normalise()
{
	float len = length();

	if (len > 0.0f)
	{
		x /= len;
		y /= len;
	}
	return len;
}

Vector2 Vector2::midPoint(const Vector2& v) const
{
	return Vector2(
		(x + v.x) * 0.5f,
		(y + v.y) * 0.5f);
}

Vector2 Vector2::normal() const
{
	return Vector2(-y, x);
}

const Vector2 Vector2::ZERO(0, 0);
const Vector2 Vector2::UNIT_X(1, 0);
const Vector2 Vector2::UNIT_Y(0, 1);
const Vector2 Vector2::NEGATIVE_UNIT_X(-1, 0);
const Vector2 Vector2::NEGATIVE_UNIT_Y(0, -1);
const Vector2 Vector2::UNIT_SCALE(1, 1);