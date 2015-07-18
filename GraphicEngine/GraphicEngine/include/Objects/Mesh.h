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
	Geometry& getGeometry();
	MaterialSPtr& getMaterial();

	GLuint mVerticesBuffer;
	GLuint mIndicesBuffer;
	GLuint mUvsBuffer;
	GLuint mNormalsBuffer;

protected:

	Geometry mGeometry;
	MaterialSPtr mMaterial;

	bool mUseVBO;

	bool mHasNormals;
	bool mHasUvs;

};

typedef std::shared_ptr<Mesh> MeshSPtr;

#endif