#include "Materials/ShaderProgram.h"
#include "Utils/Utils.h"

ShaderProgram::ShaderProgram(const std::string& name, ShaderType type, Shader* shader)
	: m_name(name),
	m_type(type),
	m_shader(shader),
	m_isAttached(false)
{
	
}

ShaderProgram::ShaderProgram(const ShaderProgram& other)
	: m_name(other.m_name),
	m_type(other.m_type),
	m_shader(other.m_shader),
	m_isAttached(false)
{

}

ShaderProgram::~ShaderProgram()
{
	
}

std::string ShaderProgram::getName() const
{
	return m_name;
}

ShaderType ShaderProgram::getShaderType() const
{
	return m_type;
}

Shader* ShaderProgram::getShader() const
{
	return m_shader;
}

void ShaderProgram::attach(bool attach)
{
	m_isAttached = attach;
}

bool ShaderProgram::isAttached() const
{
	return m_isAttached;
}

// Ce qu'il faut bien comprendre c'est que le check si le parameter auto existe va être fait en amont
bool ShaderProgram::setParameter(const std::string& name, const std::string& typeParameter, const std::string& attributeOrUniform, const std::string& typeData, const std::vector<std::string>& values)
{
	if (typeParameter == "param_named_auto")
		return setParameterAuto(name, attributeOrUniform, typeData, values);
	else if (typeParameter != "param_named")
		return false;

	// Ici on sait que ce n'est pas un paramètre auto
	// Ici on ne peut gérer que le cas des float
	int nbFloat = 0;
	std::vector<std::string> elements = Utils::split(typeData, '_');
	std::string type = elements.front();
	if (type == "float")
	{
		nbFloat = std::atoi(elements.back().c_str());

		if (nbFloat == 0)
			return false;

		FloatParameter fp(typeData);

		for (uint i = 0; i < values.size(); ++i)						// On convertit
			fp.addData(std::atof(values.at(i).c_str()));
		for (uint i = values.size(); i < nbFloat; ++i)					// On complète
			fp.addData(0.f);
		for (uint i = nbFloat, end = fp.values.size(); i < end; ++i)	// On enlève s'il y en a trop
			fp.popData();

		m_uniforms_noauto.insert(std::pair<std::string, FloatParameter>(name, fp));			
	}

	return true;
}

bool ShaderProgram::setParameterAuto(const std::string& name, const std::string& attributeOrUniform, const std::string& typeData, const std::vector<std::string>& values)
{
	if (attributeOrUniform == "attribute")
	{
		ShaderParameter sp(typeData);
		m_attributes_auto.insert(std::pair<std::string, ShaderParameter>(name, sp));
	}
	else if (attributeOrUniform == "uniform")
	{
		if (typeData == "sampler")
		{
			if (values.size() < 0)
				return false;

			StringParameter sp(typeData);
			sp.addData(values.at(0));
			m_samplers.insert(std::pair<std::string, StringParameter>(name, sp));
		}
		else
		{
			ShaderParameter sp(typeData);
			m_uniforms_auto.insert(std::pair<std::string, ShaderParameter>(name, sp));
		}
	}

	return true;
}