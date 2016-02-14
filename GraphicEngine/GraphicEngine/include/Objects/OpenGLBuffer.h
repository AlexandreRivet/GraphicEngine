#ifndef _OPENGLBUFFER_H_
#define _OPENGLBUFFER_H_

#include <memory>

#include "prerequisites.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Objects/Geometry.h"
#include "GL/glew.h"

#include "Materials\Shader.h"

struct BufferInfo
{
	GLuint id;

	uint itemSize;
	uint numItems;

	BufferInfo()
		: id(0),
		itemSize(0),
		numItems(0)
	{
	}

	BufferInfo(const BufferInfo& bi)
		: id(bi.id),
		itemSize(bi.itemSize),
		numItems(bi.numItems)
	{
	}
};

class OpenGLBuffer
{
public:
	
	OpenGLBuffer(const floatVector& vertices, const uintVector& indices, const std::vector<floatVector>& uvs = std::vector<floatVector>(), const floatVector& colors = floatVector(),
		const floatVector& normals = floatVector(), const floatVector& tangents = floatVector(), const floatVector& binormals = floatVector());

	BufferInfo* mVertexBuffer;
	BufferInfo* mIndexBuffer;
	BufferInfo* mColorBuffer;
	BufferInfo* mNormalBuffer;
	BufferInfo* mTangentBuffer;
	BufferInfo* mBinormalBuffer;
	std::vector<BufferInfo*> mUvsBuffer;

private:
	
};

template <typename T> BufferInfo* createBuffer(GLuint type, T data, uint itemSize, uint numItems);

#endif