#pragma once
#include "api.h"

class MainMenu : public Scene
{
public:
	~MainMenu();
private:
	// Inherited via Scene
	virtual void OnAttach() override;
	virtual void Start() override;
	virtual void OnDetach() override;

};

inline MainMenu::~MainMenu()
{
}
