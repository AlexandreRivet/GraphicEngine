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

GLuint Shader::attribute(std::string name)
{
	auto attr = mAttributes.find(name);
	if (attr == mAttributes.end())
	{
		mAttributes[name] = glGetAttribLocation(mProgramId, name.data());
	}

	return mAttributes[name];
}

GLuint Shader::uniform(std::string name)
{
	auto unif = mUniforms.find(name);
	if (unif == mUniforms.end())
	{
		mUniforms[name] = glGetAttribLocation(mProgramId, name.data());
	}

	return mUniforms[name];
}

bool Shader::hasAttribute(std::string name)
{
	auto attr = mAttributes.find(name);
	if (attr == mAttributes.end())
	{
		GLuint result = glGetAttribLocation(mProgramId, name.data());;
		if (result == -1)
		{
			return false;
		}
		mAttributes[name] = result;
	}

	return true;
}

bool Shader::hasUniform(std::string name)
{
	auto unif = mUniforms.find(name);
	if (unif == mUniforms.end())
	{
		GLuint result = glGetAttribLocation(mProgramId, name.data());;
		if (result == -1)
		{
			return false;
		}
		mUniforms[name] = result;
	}

	return true;
}

void Shader::setUniform(std::string name, int val)
{
	GLuint unif = uniform(name);

	if (unif > 0)
		glUniform1i(unif, val);
}

void Shader::setUniform(std::string name, float f)
{
	GLuint unif = uniform(name);

	if (unif > 0)
		glUniform1f(unif, f);
}

void Shader::setUniform(std::string name, float f1, float f2)
{
	GLuint unif = uniform(name);

	if (unif > 0)
		glUniform2f(unif, f1, f2);
}

void Shader::setUniform(std::string name, float f1, float f2, float f3)
{
	GLuint unif = uniform(name);

	if (unif > 0)
		glUniform3f(unif, f1, f2, f3);
}

void Shader::setUniform(std::string name, const Vector3& v)
{
	GLuint unif = uniform(name);

	if (unif > 0)
		glUniform3f(unif, v.x, v.y, v.z);
}

void Shader::setUniform(std::string name, const Matrix3 &m)
{
	GLuint unif = uniform(name);

	if (unif > 0)
		glUniformMatrix3fv(unif, 1, GL_TRUE, NULL);				// TODO: faire m3.toArray
}

void Shader::setUniform(std::string name, const Matrix4 &m)
{
	GLuint unif = uniform(name);

	if (unif > 0)
		glUniformMatrix4fv(unif, 1, GL_TRUE, NULL);				// TODO: faire m4.toArray
}

void Shader::setUniform(std::string name, bool b)
{
	GLuint unif = uniform(name);

	if (unif > 0)
		glUniform1i(unif, b?1:0);
}