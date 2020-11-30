#pragma once
class Player;

class ICommandBuilder
{
private:
public:
	ICommandBuilder();
	virtual ~ICommandBuilder() = 0;

	virtual void linkCommandsToPlayer(Player& character) = 0;
	virtual void initFactory() = 0;
};