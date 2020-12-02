#pragma once
class Player;
class GameKeypressInvoker;
class ICommandBuilder
{
public:
	virtual void initFactory() = 0;

	GameKeypressInvoker* getKeypressInvoker() { return keypressInvoker; }
protected:
	GameKeypressInvoker* keypressInvoker;
};