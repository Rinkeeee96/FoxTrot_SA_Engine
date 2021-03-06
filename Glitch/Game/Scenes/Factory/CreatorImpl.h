#pragma once


#ifndef _CREATORIMPL_H_
#define _CREATORIMPL_H_

#include <string>

#include "Creator.h"
#include "FactoryMethod.h"

/// @brief Template class for creator
/// @tparam T 
template <class T>
class CreatorImpl : public Creator
{
public:
	void registerClass(const string& classname, shared_ptr<SceneFactory> factory) { factory->registerit(classname, this); };
	unique_ptr<Scene> create(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) { return unique_ptr<T>{new T(id, engine, _statemachine)}; }
};


#endif //_CREATORIMPL_H_