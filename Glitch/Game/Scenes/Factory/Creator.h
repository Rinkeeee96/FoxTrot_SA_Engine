#pragma once


#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <string>

class Gate;

class Creator
{
public:
	Creator() {};
	virtual ~Creator() {};

	virtual shared_ptr<Scene> create(const int id) = 0;

};

#endif //_CREATOR_H_