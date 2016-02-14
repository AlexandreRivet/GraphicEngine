#include "Materials/Material.h"

Material::Material(const std::string& name)
: m_name(name)
{

}

Material::~Material()
{
}

Pass* Material::addPass(const std::string& name, Pass* p)
{
	std::map<std::string, Pass*>::iterator it;

	it = m_passList.find(name);
	if (it != m_passList.end())
		return (*it).second;

	m_passList.insert(std::pair<std::string, Pass*>(name, p));

	return p;
}

Pass* Material::getPass(const std::string& name)
{
	std::map<std::string, Pass*>::iterator it = m_passList.find(name);
	if (it != m_passList.end())
		return (*it).second;

	return nullptr;
}

std::map<std::string, Pass*> Material::getPassList() const
{
	return m_passList;
}