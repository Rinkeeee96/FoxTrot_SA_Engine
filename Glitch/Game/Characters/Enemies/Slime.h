#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

/// @brief 
/// Slime class with correspondending AI logic
class Slime : public IEnemy {
public:
	Slime() : IEnemy() {}
	Slime(const int id) : IEnemy(id) {}

	void onUpdate() override {
		
	};

	void setYAxisVelocity(const float val) override {
		if (this->getYAxisVelocity() == 0) {
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
		}

		Object::setYAxisVelocity(val);
	}

	ICharacter* clone(int id) override { return new Slime(id); }
};