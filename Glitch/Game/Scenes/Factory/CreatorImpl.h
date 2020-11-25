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
	void registerClass(const string& classname, Factory* factory) { factory->registerit(classname, this); };

	virtual shared_ptr<Scene> create(const int id) { return shared_ptr<T>{new T(id)}; }
};



#endif //_CREATORIMPL_H_