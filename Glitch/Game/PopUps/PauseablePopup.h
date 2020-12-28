#include "IPopup.h"

class PauseablePopup : public IPopup
{
public:
	PauseablePopup(unique_ptr<Engine>& _engine, EventDispatcher& _dispatcher, shared_ptr<SceneStateMachine> _stateMachine) :
		IPopup(_engine, _dispatcher, _stateMachine) {};

	virtual void setupPopUp() override = 0;
	virtual void cleanPopUp() override = 0;
	
	virtual void onUpdate() override = 0;

	virtual void onAttach() override
	{
		this->setupPopUp();
		setAlwaysVisible(true);

		if (this->stateMachine->activePopupCount() <= 1) {
			TogglePauseEvent pauseEvent(true);
			dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
		}
	};

	virtual void onDetach() override 
	{
		this->cleanPopUp();
		setAlwaysVisible(false);

		if (this->stateMachine->activePopupCount() <= 1) {
			TogglePauseEvent pauseEvent(false);
			dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
		}
	};
};