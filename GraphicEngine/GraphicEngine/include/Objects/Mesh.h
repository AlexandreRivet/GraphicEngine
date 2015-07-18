#ifndef _MESH_H_
#define _MESH_H_

#include "Objects/Object3D.h"
#include "Objects/Geometry.h"
#include "Materials/Material.h"

class Mesh: public Object3D
{
public:

	Mesh();
	Mesh(Geometry geo, MaterialSPtr mat, bool useVBO = true);
	~Mesh();

	void initVBO();
	void checkUpdate();
	void updateVBO();

	void draw() const;
	void drawWithVBO() const;
	void drawWithoutVBO() const;

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


#endif