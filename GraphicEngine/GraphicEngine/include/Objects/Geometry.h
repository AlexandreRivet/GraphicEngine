#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "prerequisites.h"

class Geometry
{
public:

	Geometry(const std::vector<float>& vertices, const std::vector<uint>& indices, const std::vector<float>& uvs = std::vector<float>(), const std::vector<float>& normals = std::vector<float>());

	void setVertices(const std::vector<float>& vertices);
	void setIndices(const std::vector<uint>& indices);
	void setUvs(const std::vector<float>& uvs);
	void setNormals(const std::vector<float>& normals);

	const std::vector<float>& getVertices() const;
	const std::vector<uint>& getIndices() const;
	const std::vector<float>& getUvs() const;
	const std::vector<float>& getNormals() const;

	int getNbVertices() const;
	int getNbIndices() const;
	int getNbUvs() const;
	int getNbNormals() const;

	bool hasUvs() const;
	bool hasNormals() const;
	inline bool needsUpdate() const;
	inline void setNeedsUpdate(bool update); 

protected:

	std::vector<float> mVertices;
	std::vector<uint> mIndices;
	std::vector<float> mUvs;
	std::vector<float> mNormals;

	bool mHasNormals;
	bool mHasUvs;
	bool mNeedsUpdate;

};

#endif