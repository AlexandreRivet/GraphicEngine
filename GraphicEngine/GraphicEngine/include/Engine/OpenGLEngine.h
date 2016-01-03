#ifndef _OPENGLENGINE_H_
#define _OPENGLENGINE_H_

#include "Utils/freeglut_include.h"

#include "Engine/Engine.h"
#include "Render/Renderer.h"

class OpenGLEngine : public Engine
{
public:

	GLuint lol;
	Renderer* mRenderer;

private:

};

#endif