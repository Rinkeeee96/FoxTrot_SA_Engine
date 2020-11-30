#pragma once


#ifndef _CREATORIMPL_H_
#define _CREATORIMPL_H_

#include <string>

#include "Creator.h"
#include "FactoryMethod.h"

template <class T>
class CreatorImpl : public Creator
{
public:
	CreatorImpl() {};
	~CreatorImpl() {};
	void registerClass(const string& classname, shared_ptr<SceneFactory> factory) { factory->registerit(classname, this); };

	virtual shared_ptr<Scene> create(const int id, Engine& engine) { return shared_ptr<T>{new T(id, engine)}; }
};



#endif //_CREATORIMPL_H_