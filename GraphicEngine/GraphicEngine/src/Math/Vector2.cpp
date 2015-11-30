#include "Math/Vector2.h"

const Vector2 Vector2::ZERO(0, 0);

const Vector2 Vector2::UNIT_X(1, 0);
const Vector2 Vector2::UNIT_Y(0, 1);
const Vector2 Vector2::NEGATIVE_UNIT_X(-1, 0);
const Vector2 Vector2::NEGATIVE_UNIT_Y(0, -1);
const Vector2 Vector2::UNIT_SCALE(1, 1);

bool intersection(Vector2& sA, Vector2& sB, Vector2& dA, Vector2& dB, Vector2& inter)
{
	// Equation param�trique d'une droite � partir de deux points
	// P(t) = sA + (sB - sA)t
	// Q(s) = dA + (dB - dA)s
	// ^ * X = b 

	// D�finition de la matrice 2x2 -> ^
	float matrix[2][2];
	matrix[0][0] = sB.x - sA.x;
	matrix[0][1] = dA.x - dB.x;
	matrix[1][0] = sB.y - sA.y;
	matrix[1][1] = dA.y - dB.y;

	// Calcul du d�terminant
	float determinant = (sB.x - sA.x) * (dA.y - dB.y) - (sB.y - sA.y) * (dA.x - dB.x);

	// On quitte si le d�terminant est nul
	if (determinant == 0.0f)
		return false;

	// On calcul l'inverse de la matrice -> ^-1
	float invmatrix[2][2];
	invmatrix[0][0] = matrix[1][1] * (1 / determinant);
	invmatrix[0][1] = -matrix[0][1] * (1 / determinant);
	invmatrix[1][0] = -matrix[1][0] * (1 / determinant);
	invmatrix[1][1] = matrix[0][0] * (1 / determinant);

	// D�finition du b
	float bMatrix[2];
	bMatrix[0] = dA.x - sA.x;
	bMatrix[1] = dA.y - sA.y;

	// R�sultat de la multiplication -> ^-1 * b
	float X[2];
	// correspond � t
	X[0] = invmatrix[0][0] * bMatrix[0] + invmatrix[0][1] * bMatrix[1];

	// correspond � s
	X[1] = invmatrix[1][0] * bMatrix[0] + invmatrix[1][1] * bMatrix[1];

	inter = sA + (sB - sA) * X[0];
	return true;
}