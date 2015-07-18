#ifndef _MESH_H_
#define _MESH_H_

#include "Objects/Geometry.h"
#include "Materials/Material.h"

class Mesh
{
public:

	Mesh();
	Mesh(Geometry geo, MaterialSPtr mat, bool useVBO = true);
	~Mesh();

	void initBuffers();

protected:

	Geometry mGeometry;
	MaterialSPtr mMaterial;

	GLuint mVerticesBuffer;
	GLuint mIndicesBuffer;
	GLuint mUvsBuffer;
	GLuint mNormalsBuffer;

	bool mUseVBO;

	bool mHasNormals;
	bool mHasUvs;

};

typedef std::shared_ptr<Mesh> MeshSPtr;

#endif