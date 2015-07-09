#include "Materials/Material.h"

#include "Materials/ShaderLoader.h"

Material::Material(const std::string& name)
{
	mShader = ShaderLoader::getShader(name);
}

Material::Material(ShaderSPtr s)
{
	mShader = s;
}

ShaderSPtr Material::getShader()
{
	return mShader;
}