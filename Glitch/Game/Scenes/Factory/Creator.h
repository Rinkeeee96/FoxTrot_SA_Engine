#pragma once


#ifndef _CREATOR_H_
#define _CREATOR_H_

class Engine;
class SceneStateMachine;

/// @brief Creator class for Scene's
class Creator
{
public:
	Creator() {};
	~Creator() {};

	virtual Scene* create(const int id, Engine& engine, SceneStateMachine& _statemachine) = 0;

};

#endif //_CREATOR_H_