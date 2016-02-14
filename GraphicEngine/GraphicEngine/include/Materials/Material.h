#ifndef _MATERIALS_H_
#define _MATERIALS_H_

#include "Materials/Pass.h"

class Material
{
public:
	
	Material(const std::string& name);
	~Material();

	Pass* addPass(const std::string& name, Pass* p);
	Pass* getPass(const std::string& name);
	std::map<std::string, Pass*> getPassList() const;

protected:					// protected ou private => tout dépendra si on fait des material qui dérivent et qui en ont besoin

	std::string m_name;
	std::map<std::string, Pass*> m_passList;

};

#endif