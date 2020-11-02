#pragma once
#include "Commands.h"
#include "IInputFacade.h"

#include "InputConstants.h"
#include "Events/Codes/KeyCodes.h"
#include "./Events/EventSingleton.h"
#include "./Events/Key/KeyPressed.h"
#include "./Events/Key/KeyReleased.h"
#include "./Events/Mouse/MouseMoved.h"
#include "./Events/Mouse/MousePressed.h"
#include "./Events/Mouse/MouseReleased.h"
#include "./Events/Mouse/MouseScrolledEvent.h"

union SDL_Event;



/// @brief Facade for SDL input part
class InputFacade : public IInputFacade
{

public:
    InputFacade();
    ~InputFacade();

	bool fill(vector<Command*>& command_queue);
	void configure(KeyCode key, Command* command);
private:
	bool input_mapping();
	void dispatcher(std::vector<Command*>& command_queue);

	void keydown(SDL_Event& event);
	void keyup(SDL_Event& event);

	bool is_held(int key);
	bool was_pressed(int key);

	void pollEvents() override;

	map <KeyCode, State> state_map;
	map <KeyCode, Action> action_map;

	map <KeyCode, Command*> commands;

	KeyCode eventToKeyCode(SDL_Event& event);
};



