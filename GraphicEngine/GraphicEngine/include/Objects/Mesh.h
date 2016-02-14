#ifndef _MESH_H_
#define _MESH_H_

#include "Objects/Geometry.h"
#include "Materials/Material.h"
#include "Objects/OpenGLBuffer.h"


class Mesh
{
public:

	Mesh();
	Mesh(Geometry geo, Material* mat);
	~Mesh();

	void initBuffers();
	Geometry& getGeometry();
	Material* getMaterial();
	OpenGLBuffer& getBuffers();

protected:

	Geometry mGeometry;
	Material* mMaterial;
	OpenGLBuffer mBuffers;

};

typedef std::shared_ptr<Mesh> MeshSPtr;

#endif