#include "link.h"

using namespace std;

Link::Link(char name, char type, int strength, int player): name{name}, type{type},
			strength{strength}, player{player}, isBoosted{false} {}

LInfo Link::getInfo() const {
<<<<<<< HEAD
	LInfo info{this->player, this->name, this->isBoosted}; // Return relevant LInfo
=======
	return LInfo {this->player, this->name, this->isBoosted};
>>>>>>> 9cf932c33891c5e031d0d2de13b271c7b6f1a3f5
}

void Link::reveal() {
	this->setState(LState{StateType::Reveal, this->name}); // Sets LState to Reveal
				// with the name of the link to be revealed
	this->notifyObservers(); // Notifies observers of this change to Link
}

char Link::getType() {
	return this->type;
}

void Link::setType(char type){
	this->type = type;
}

int Link::getStrength() {
	return this->strength;
}

void Link::setBoosted(bool boosted){
	this->isBoosted = boosted;
}
