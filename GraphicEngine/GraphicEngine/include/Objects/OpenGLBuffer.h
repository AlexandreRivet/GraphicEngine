#ifndef _OPENGLBUFFER_H_
#define _OPENGLBUFFER_H_

#include "prerequisites.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Objects/Geometry.h"
#include "GL/glew.h"



struct VertexData
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv1;
	Vector2 uv2;
	Vector3 tangent;
	Vector3 binormal;
};

class OpenGLBuffer
{
public:
	
	OpenGLBuffer();

	void bind() const;
	void unbind() const;
	void pushVertices(const std::vector<VertexData>& newVertices, const std::vector<VertexData>& allVertices);
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