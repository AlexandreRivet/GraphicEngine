#ifndef _TYPES_H_
#define _TYPES_H_

#include "config.h"

#include <cassert>
#include <cmath>

#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>

#if DOUBLE_PRECISION == 1
	typedef double Real;
#else 
	typedef float Real;
#endif

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

class Matrix3;
class Matrix4;
class Quaternion;
class Vector2;
class Vector3;


#endif