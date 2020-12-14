#pragma once
#include "Game/Commands/ICharacterCommand.h"
#include "Game/States/Player/GodState.h"
class GodmodeCommand : public ICharacterCommand
{
public:
	GodmodeCommand(ICharacter& _character, string identifier) : ICharacterCommand(_character, identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		// only the player can enforce godmode
		if (typeid(character) != typeid(Player))
			return;
		
		Player& player = dynamic_cast<Player&>(character);

		IState<Player>& currentState = player.getStateMachine().getCurrentState();

		if (typeid(currentState).name() == typeid(NormalState).name())
			player.getStateMachine().changeState(new GodState, &player);
		else 
			player.getStateMachine().changeState(new NormalState, &player);
	}
};
