#include "Objects\ObjectLoader.h"
#include "Materials\MaterialManager.h"

#include "tiny_obj_loader.h"

ObjectLoader::ObjectLoader()
{}

Object3D ObjectLoader::load(const std::string& filename, bool mergeObjects)
{
	std::string extension = Utils::split(filename, '.').back();

	if (extension == "obj")
		return _loadOBJ(filename, mergeObjects);
	else if (extension == "fbx")
		return _loadFBX(filename, mergeObjects);

	return Object3D();
}

Object3D ObjectLoader::_loadOBJ(const std::string& filename, bool mergeObjects)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, filename.c_str());
	
	std::string pathResource = filename.substr(0, filename.find_last_of('/'));

	Object3D root(Utils::split(Utils::split(filename, '/').back(), '.').front());

	if (mergeObjects)
	{
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
			std::vector<floatVector>({ texcoords }),
			floatVector(),
			normals
		);

		// Dans le cas du merge on ne prend que le premier material
		std::string name = shapes.at(0).name;
		uint id_mat = shapes.at(0).mesh.material_ids.at(0);
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
	else
	{
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
	}

	return root;
}

Object3D ObjectLoader::_loadFBX(const std::string&, bool)
{
	return Object3D();
}