#pragma once


#ifndef _CREATORIMPL_H_
#define _CREATORIMPL_H_

#include <string>

#include "Creator.h"

template <class T>
class CreatorImpl : public Creator
{
public:
	CreatorImpl<T>(const std::string& classname) : Creator(classname) {}
	virtual ~CreatorImpl<T>() {}

	virtual shared_ptr<Scene> create() { return shared_ptr<T>{new T}; }
};



#endif //_CREATORIMPL_H_