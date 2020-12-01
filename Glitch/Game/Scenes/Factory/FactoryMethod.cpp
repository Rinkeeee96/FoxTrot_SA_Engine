#include "pch.h"
#include "FactoryMethod.h"
#include "Creator.h"

void SceneFactory::registerit(const std::string& classname, Creator* creator)
{
	table[classname] = creator;
}

shared_ptr<Scene> SceneFactory::create(const std::string& classname, const int id, Engine& engine, SceneStateMachine& _stateMachine)
{
	std::map<std::string, Creator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->create(id, engine, _stateMachine);
	else
		return (shared_ptr<Scene>)NULL;
}