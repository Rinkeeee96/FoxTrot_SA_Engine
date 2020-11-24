#pragma once

#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <string>
#include <map>


class Scene;
class Creator;

class Factory
{
public:
	static shared_ptr<Scene> create(const std::string& classname);
	static void registerit(const std::string& classname, Creator* creator);
private:
	static std::map<std::string, Creator*>& get_table();
};

#endif //_FACTORY_H_
