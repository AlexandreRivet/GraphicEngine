#ifndef _OPENGLBUFFER_H_
#define _OPENGLBUFFER_H_

#include <memory>

#include "prerequisites.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Objects/Geometry.h"
#include "GL/glew.h"

#include "Materials\Shader.h"

class OpenGLBuffer
{
public:
	
	OpenGLBuffer();

	void bind() const;
	void unbind() const;
	void pushVertices(const std::vector<ShaderData>& newVertices, const std::vector<ShaderData>& allVertices);
	void pushIndices(const std::vector<float>& newIndices, const std::vector<float>& allIndices);
	void updateGeometry(const Geometry& geo);

	struct BufferInfo
	{
		GLuint id;
		uint capacity;
	};

	BufferInfo mVBO;
	BufferInfo mVAO;
	BufferInfo mIBO;

private:
	
};

#endif