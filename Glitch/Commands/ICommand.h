#pragma once
class ICommand
{
public:
	ICommand() {};
	virtual void execute() const = 0;
};