#include "Objects\ObjectLoader.h"
#include "Materials\BasicMaterial.h"

#include "tiny_obj_loader.h"

ObjectLoader::ObjectLoader()
{}

Object3D ObjectLoader::load(const std::string& filename)
{
	std::string extension = Utils::split(filename, '.').back();

	if (extension == "obj")
		return _loadOBJ(filename);
	else if (extension == "fbx")
		return _loadFBX(filename);
}

Object3D ObjectLoader::_loadOBJ(const std::string& filename)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, filename.c_str());

	// On merge tout mouahaha
	std::vector<uint> indices;
	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<float> texcoords;

	uint nbPrevVertices = 0;
	for (auto it = shapes.begin(); it != shapes.end(); ++it)
	{
		tinyobj::shape_t shape = *it;

		// positions
		for (auto jt = shape.mesh.positions.begin(); jt != shape.mesh.positions.end(); ++jt)
		{
			positions.push_back(*jt);
		}

		// indices
		for (auto jt = shape.mesh.indices.begin(); jt != shape.mesh.indices.end(); ++jt)
		{
			indices.push_back(*jt + nbPrevVertices);
		}

		// texcoords
		for (auto jt = shape.mesh.texcoords.begin(); jt != shape.mesh.texcoords.end(); ++jt)
		{
			texcoords.push_back(*jt);
		}

		// normals
		for (auto jt = shape.mesh.normals.begin(); jt != shape.mesh.normals.end(); ++jt)
		{
			normals.push_back(*jt);
		}

		nbPrevVertices += shape.mesh.positions.size() / 3;
	}

	Geometry geo = Geometry(
		positions,
		indices,
		texcoords,
		normals
	);

	// On prend que le materials 0
	BasicMaterial* bm;
	if (materials.size() > 0 && !materials[0].diffuse_texname.empty())
	{
		bm = new BasicMaterial("textured", Vector3(0.0f, 0.0f, 0.0f), materials[0].diffuse_texname);
	}
	else
	{
		bm = new BasicMaterial("simple", Vector3(0.0f, 0.0f, 1.0f));
	}

	MaterialSPtr msptr(bm);
	MeshSPtr mesh(new Mesh(geo, msptr));

	std::string name = Utils::split(Utils::split(filename, '/').back(), '.').front();
	
	return Object3D(name, mesh);
}

Object3D ObjectLoader::_loadFBX(const std::string& filename)
{
	return Object3D();
}