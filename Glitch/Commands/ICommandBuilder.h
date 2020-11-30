#pragma once
class Player;

class ICommandBuilder
{
private:
public:
	virtual void linkCommandsToPlayer(Player& character) = 0;
	virtual void initFactory() = 0;
};