#include "Materials/Shader.h"

#include "Utils/Utils.h"

Shader::Shader(GLuint prog, GLuint vs, GLuint fs, GLuint gs)
	: mProgramId(prog),
	mVertexShaderId(vs),
	mFragmentShaderId(fs),
	mGeometryShaderId(gs)
{

}

Shader::~Shader()
{
	if (mProgramId)
	{
		if (mVertexShaderId)
		{
			glDetachShader(mProgramId, mVertexShaderId);
			glDeleteShader(mVertexShaderId);
		}

		if (mFragmentShaderId)
		{
			glDetachShader(mProgramId, mFragmentShaderId);
			glDeleteShader(mFragmentShaderId);
		}

		if (mGeometryShaderId)
		{
			glDetachShader(mProgramId, mGeometryShaderId);
			glDeleteShader(mGeometryShaderId);
		}

		glDeleteProgram(mProgramId);
	}
}

void Shader::bind() const
{
	glUseProgram(mProgramId);
}


void Shader::unbind() const
{
	glUseProgram(0);
}

GLint Shader::attribute(const std::string& name)
{
	auto attr = mAttributes.find(name);
	if (attr == mAttributes.end())
	{
		mAttributes[name] = glGetAttribLocation(mProgramId, name.data());
	}

	return mAttributes[name];
}

GLint Shader::uniform(const std::string& name)
{
	auto unif = mUniforms.find(name);
	if (unif == mUniforms.end())
	{
		mUniforms[name] = glGetUniformLocation(mProgramId, name.data());
	}	

	return mUniforms[name];
}

bool Shader::hasAttribute(const std::string& name)
{
	auto attr = mAttributes.find(name);
	if (attr == mAttributes.end())
	{
		GLint result = glGetAttribLocation(mProgramId, name.data());
		if (result == -1)
		{
			return false;
		}
		mAttributes[name] = result;
	}

	return true;
}

bool Shader::hasUniform(const std::string& name)
{
	auto unif = mUniforms.find(name);
	if (unif == mUniforms.end())
	{
		GLint result = glGetUniformLocation(mProgramId, name.data());
		if (result == -1)
		{
			return false;
		}
		mUniforms[name] = result;
	}

	return true;
}

void Shader::setUniform(const std::string& name, Texture& tex)
{
	GLint unif = uniform(name);

	if (unif >= 0)
		glUniform1i(unif, tex.mIndex);
}

void Shader::setUniform(const std::string& name, int val)
{
	GLint unif = uniform(name);

	if (unif >= 0)
		glUniform1i(unif, val);
}

void Shader::setUniform(const std::string& name, float f)
{
	GLint unif = uniform(name);

	if (unif >= 0)
		glUniform1f(unif, f);
}

void Shader::setUniform(const std::string& name, float f1, float f2)
{
	GLint unif = uniform(name);

	if (unif >= 0)
		glUniform2f(unif, f1, f2);
}

void Shader::setUniform(const std::string& name, float f1, float f2, float f3)
{
	GLint unif = uniform(name);

	if (unif >= 0)
		glUniform3f(unif, f1, f2, f3);
}

void Shader::setUniform(const std::string& name, float* ptr, uint size)
{
	GLint unif = uniform(name);

	if (unif >= 0)
		glUniform1fv(unif, size, ptr);
}


void Shader::setUniform(const std::string& name, const Vector3& v)
{
	GLint unif = uniform(name);

	if (unif >= 0)
		glUniform3f(unif, v.x, v.y, v.z);
}

void Shader::setUniform(const std::string& name, const Matrix3 &m)
{
    tools::unusedArg(m);

	GLint unif = uniform(name);

	if (unif >= 0)
		glUniformMatrix3fv(unif, 1, GL_FALSE, NULL);				// TODO: faire m3.toArray
}

void Shader::setUniform(const std::string& name, const Matrix4 &m)
{
	GLint unif = uniform(name);

	if (unif >= 0)
	{
		float arr[16];
		m.toArray(arr);
		glUniformMatrix4fv(unif, 1, GL_FALSE, arr);
	}
		
}

void Shader::setUniform(const std::string& name, bool b)
{
	GLint unif = uniform(name);

	if (unif >= 0)
		glUniform1i(unif, b?1:0);
}