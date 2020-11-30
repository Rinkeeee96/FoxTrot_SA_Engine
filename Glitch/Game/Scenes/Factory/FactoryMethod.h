#pragma once

#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <string>
#include <map>


class Scene;
class Creator;

class SceneFactory
{
public:
	SceneFactory() {};
	~SceneFactory() {};
	shared_ptr<Scene> create(const std::string& classname, const int id);
	void registerit(const std::string& classname, Creator* creator);
private:
	std::map<std::string, Creator*> table; 
};

#endif //_FACTORY_H_
