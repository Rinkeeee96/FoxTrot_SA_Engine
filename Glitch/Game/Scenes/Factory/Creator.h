#pragma once


#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <string>

class Gate;

class Creator
{
public:
	Creator(const std::string& classname);
	virtual ~Creator() {};

	virtual shared_ptr<Scene> create() = 0;
};

#endif //_CREATOR_H_