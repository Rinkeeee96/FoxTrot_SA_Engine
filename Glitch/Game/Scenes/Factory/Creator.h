#pragma once


#ifndef _CREATOR_H_
#define _CREATOR_H_

class Engine;

class Creator
{
public:
	Creator() {};
	~Creator() {};

	virtual shared_ptr<Scene> create(const int id, Engine& engine) = 0;

};

#endif //_CREATOR_H_