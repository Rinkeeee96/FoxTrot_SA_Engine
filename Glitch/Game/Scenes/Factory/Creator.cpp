#include "pch.h"
#pragma once


#include "Creator.h"
#include "FactoryMethod.h"

Creator::Creator(const std::string& classname)
{
	Factory::registerit(classname, this);
}