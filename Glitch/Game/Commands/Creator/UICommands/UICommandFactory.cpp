#include "pch.h"
#include "UICommandFactory.h"
#include "Game/characters/ICharacter.h"
#include "UICommandCreator.h"
#include "Engine/Input/Commands/exceptions/unknownCommandException.h"

void UICommandFactory::registerit(const std::string& classname, IUICommandCreator* creator)
{
	table[classname] = creator;
}


IUICommand* UICommandFactory::createUICommand(const std::string& classname, const int layerIndex)
{
	auto i = table.find(classname);

	if (i != table.end())
		return i->second->createUICommand(layerIndex);
	else
		throw exception(string("Unknown command " + classname).c_str());
}