#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "prerequisites.h"

class Vector3
{
public:
	// Constructeur et destructeur
	Vector3(float = 0.0f, float = 0.0f, float = 0.0f);
	Vector3(const Vector3&);
	~Vector3(void);

	// Surcharge opérateur
	float operator [] (uint) const;
	float& operator[] (uint);
	Vector3 operator + (const Vector3&) const;
	Vector3 operator + (const float) const;
	Vector3 operator - (const Vector3&) const;
	Vector3 operator - (const float) const;
	Vector3 operator * (const Vector3&) const;
	Vector3 operator * (const float) const;
	Vector3 operator / (const Vector3&) const;
	Vector3 operator / (const float) const;
	Vector3& operator += (const Vector3&);
	Vector3& operator += (const float);
	Vector3& operator -= (const Vector3&);
	Vector3& operator -= (const float);
	Vector3& operator *= (const Vector3&);
	Vector3& operator *= (const float);
	Vector3& operator /= (const Vector3&);
	Vector3& operator /= (const float);
	Vector3& operator = (const Vector3&);
	bool operator == (const Vector3&) const;
	bool operator != (const Vector3&) const;
	bool operator < (const Vector3&) const;
	bool operator > (const Vector3&) const;

	// Autres méthodes
	float length() const;
	float squaredLength() const;
	float distance(const Vector3&) const;
	float squaredDistance(const Vector3&) const;
	float dotProduct(const Vector3&) const;
	float normalise();

	// Méthode d'affichage (notamment pour le debug)
	friend std::ostream& operator << (std::ostream&, const Vector3&);

	// Constantes statiques 
	static const Vector3 ZERO;
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;
	static const Vector3 NEGATIVE_UNIT_X;
	static const Vector3 NEGATIVE_UNIT_Y;
	static const Vector3 NEGATIVE_UNIT_Z;
	static const Vector3 UNIT_SCALE;

public:
	float x, y, z;

};

typedef std::vector<Vector3> Vector3Vector;

#endif