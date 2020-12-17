#include "pch.h"
#include "FactoryMethod.h"
#include "Creator.h"

/// @brief Register a scene to the table
/// @param classname 
/// @param creator 
void SceneFactory::registerit(const std::string& classname, Creator* creator)
{
	table[classname] = creator;
}

/// @brief Creates the scene from the table
/// @param classname 
/// @param id 
/// @param engine 
/// @param _stateMachine 
/// @return 
unique_ptr<Scene> SceneFactory::create(const std::string& classname, const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _stateMachine)
{
	std::map<std::string, Creator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->create(id, engine, _stateMachine);
	else
		return nullptr;
}