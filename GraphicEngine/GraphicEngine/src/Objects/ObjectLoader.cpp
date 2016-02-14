#include "Objects\ObjectLoader.h"
#include "Materials\MaterialManager.h"

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
	
	std::string pathResource = filename.substr(0, filename.find_last_of('/'));

	Object3D root(Utils::split(Utils::split(filename, '/').back(), '.').front());

	// Ici on va biaiser le système de loading de material
	for (uint i = 0; i < shapes.size(); ++i)
	{
		tinyobj::shape_t shape = shapes.at(i);

		std::string name = shape.name;
		tinyobj::mesh_t mesh_t = shape.mesh;
		uint id_mat = mesh_t.material_ids.at(0);

		Geometry geo(mesh_t.positions, mesh_t.indices, std::vector<floatVector>({ mesh_t.texcoords }), floatVector(), mesh_t.normals);

		Material* mat = MaterialManager::getMaterial(materials.at(id_mat).name);
		if (mat == nullptr)
		{
			std::string materialFile = pathResource;
			materialFile = materialFile.append("/" + materials.at(id_mat).name + ".mat");
			MaterialManager::loadFromFile(materialFile);
			mat = MaterialManager::getMaterial(materials.at(id_mat).name);
		}

		MeshSPtr mesh(new Mesh(geo, mat));
		Object3D* obj = new Object3D(name, mesh);

		root.addChild(obj);
	}

	return root;
}

Object3D ObjectLoader::_loadFBX(const std::string& filename)
{
	return Object3D();
}