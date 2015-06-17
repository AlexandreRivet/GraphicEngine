#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "prerequisites.h"

class Vector2
{
	// Constructeur et destructeur
	Vector2();
	Vector2(float = 0.0f, float = 0.0f);
	Vector2(const Vector2&);
	~Vector2(void);

	// Surcharge opérateur
	Vector2 operator + (const Vector2&) const;
	Vector2 operator + (const float) const;
	Vector2 operator - (const Vector2&) const;
	Vector2 operator - (const float) const;
	Vector2 operator * (const Vector2&) const;
	Vector2 operator * (const float) const;
	Vector2 operator / (const Vector2&) const;
	Vector2 operator / (const float) const;
	Vector2& operator += (const Vector2&);
	Vector2& operator += (const float);
	Vector2& operator -= (const Vector2&);
	Vector2& operator -= (const float);
	Vector2& operator *= (const Vector2&);
	Vector2& operator *= (const float);
	Vector2& operator /= (const Vector2&);
	Vector2& operator /= (const float);
	Vector2& operator = (const Vector2&);
	bool operator == (const Vector2&) const;
	bool operator != (const Vector2&) const;
	bool operator < (const Vector2&) const;
	bool operator > (const Vector2&) const;

	// Autres méthodes
	float length() const;
	float squaredLength() const;
	float distance(const Vector2&) const;
	float squaredDistance(const Vector2&) const;
	float dotProduct(const Vector2&) const;
	float crossProduct(const Vector2&) const;
	float normalise();

	Vector2 midPoint(const Vector2&) const;
	Vector2 normal() const;

	// Méthode d'affichage (notamment pour le debug)
	friend std::ostream& operator << (std::ostream&, const Vector2&);

	// Constantes statiques 
	static const Vector2 ZERO;
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
	static const Vector2 NEGATIVE_UNIT_X;
	static const Vector2 NEGATIVE_UNIT_Y;
	static const Vector2 UNIT_SCALE;

public:
	float x, y;

};

#endif