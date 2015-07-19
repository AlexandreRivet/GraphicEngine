#ifndef _SHADER_H_
#define _SHADER_H_

#include <memory>

#include "GL/glew.h"
#include "prerequisites.h"
#include "Materials/Texture.h"

#include "Math/Vector3.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"



class Shader
{
public:

	Shader(GLuint prog, GLuint vs, GLuint fs, GLuint gs);
	~Shader();

	void bind() const;
	void unbind() const;

	GLint attribute(const std::string& name);
	GLint uniform(const std::string& name);

	bool hasAttribute(const std::string& name);
	bool hasUniform(const std::string& name);

	/* TODO: Faire les textures */
	void setUniform(const std::string& name, Texture& tex);
	void setUniform(const std::string& name, int val);
	void setUniform(const std::string& name, float f);
	void setUniform(const std::string& name, float f1, float f2);
	void setUniform(const std::string& name, float f1, float f2, float f3);
	void setUniform(const std::string& name, float* ptr, uint size);
	void setUniform(const std::string& name, const Vector3& v);
	void setUniform(const std::string& name, const Matrix3& m);
	void setUniform(const std::string& name, const Matrix4& m);
	void setUniform(const std::string& name, bool b);

private:

	GLuint mProgramId;
	GLuint mVertexShaderId;
	GLuint mFragmentShaderId;
	GLuint mGeometryShaderId;

	std::map<std::string, GLint> mUniforms;
	std::map<std::string, GLint> mAttributes;
};

typedef std::shared_ptr<Shader> ShaderSPtr;

#endif