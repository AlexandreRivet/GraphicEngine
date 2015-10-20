#ifndef _FREEGLUT_INCLUDE_H_
#define _FREEGLUT_INCLUDE_H_

#define GLEW_STATIC 1
#include "GL/glew.h"

#ifdef _WIN32
#	include <Windows.h>
#	define FREEGLUT_LIB_PRAGMAS 0
#	pragma comment(lib, "freeglut.lib")
#	pragma comment(lib, "opengl32.lib")
#	pragma comment(lib, "glew32s.lib")
#endif

#include "GL/freeglut.h"

#endif