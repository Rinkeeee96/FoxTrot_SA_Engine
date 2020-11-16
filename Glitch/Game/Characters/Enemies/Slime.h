#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

class Slime : public IEnemy {
public:
	Slime() : IEnemy() {}
	Slime(const int id) : IEnemy(id) {}

	virtual void onUpdate() override {
		
	};

	void setYAxisVelocity(const float val) override {
		if (this->getYAxisVelocity() == 0) {
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
		}

		Object::setYAxisVelocity(val);
	}

	virtual ICharacter* clone(int id) override { return new Slime(id); }
};