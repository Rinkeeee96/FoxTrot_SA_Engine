#include "pch.h"
#include "FactoryMethod.h"
#include "Creator.h"

void Factory::registerit(const std::string& classname, Creator* creator)
{
	get_table()[classname] = creator;
}

shared_ptr<Scene> Factory::create(const std::string& classname)
{
	std::map<std::string, Creator*>::iterator i;
	i = get_table().find(classname);

	if (i != get_table().end())
		return i->second->create();
	else
		return (shared_ptr<Scene>)NULL;
}

std::map<std::string, Creator*>& Factory::get_table()
{
	static std::map<std::string, Creator*> table;
	return table;
}