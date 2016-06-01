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

	void addPoint(const Vector3& p);
	void removePoint(uint index);
	void updatePoint(uint index, const Vector3& p);
	Vector3 getPointAt(uint index);

	void update();
	void setGeometry(const Geometry& geo);
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