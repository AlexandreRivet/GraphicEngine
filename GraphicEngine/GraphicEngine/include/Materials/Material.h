#ifndef _MATERIALS_H_
#define _MATERIALS_H_

#include "prerequisites.h"

#include "Materials/Shader.h"

class Material
{
public:
	
	Material(const std::string& name);
	Material(ShaderSPtr s);

	ShaderSPtr getShader();

	virtual void bind() {}

protected:

	ShaderSPtr mShader;

};

typedef std::shared_ptr<Material> MaterialSPtr;

#endif