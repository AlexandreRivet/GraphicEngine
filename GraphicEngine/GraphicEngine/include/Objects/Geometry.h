#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "prerequisites.h"

class Geometry
{
public:

	Geometry(const floatVector& vertices, const uintVector& indices, const std::vector<floatVector>& uvs = std::vector<floatVector>(), const floatVector& colors = floatVector(),
			 const floatVector& normals = floatVector(), const floatVector& tangents = floatVector(), const floatVector& binormals = floatVector());

	/* => Les set sont compliqu�s pour le moment, il faudrait notifier pour que tous les mesh qui poss�dent cette geometry se mettent � jour
	void setVertices(const std::vector<float>& vertices);
	void setIndices(const std::vector<uint>& indices);
	void setUvs(const std::vector<float>& uvs);
	void setNormals(const std::vector<float>& normals);
	*/

	const floatVector& getVertices() const;
	const uintVector& getIndices() const;
	const std::vector<floatVector>& getUvs() const;
	const floatVector& getNormals() const;
	const floatVector& getColors() const;
	const floatVector& getTangents() const;
	const floatVector& getBinormals() const;

	uint getNbVertices() const;
	uint getNbIndices() const;
	uint getNbUvs() const;
	uint getNbNormals() const;
	uint getNbColors() const;
	uint getNbTangents() const;
	uint getNbBinormals() const;

protected:

	floatVector					mVertices;
	uintVector					mIndices;
	std::vector<floatVector>	mUvs;
	floatVector					mNormals;
	floatVector					mColors;
	floatVector					mTangents;
	floatVector					mBinormals;

};

#endif