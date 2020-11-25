#include "pch.h"
#include "FactoryMethod.h"
#include "Creator.h"

void Factory::registerit(const std::string& classname, Creator* creator)
{
	table[classname] = creator;
}

shared_ptr<Scene> Factory::create(const std::string& classname, const int id)
{
	std::map<std::string, Creator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->create(id);
	else
		return (shared_ptr<Scene>)NULL;
}