#include "link.h"

using namespace std;

Link::Link(char name, char type, int strength, int player): name{name}, type{type},
			strength{strength}, player{player}, isBoosted{false} {}

LInfo Link::getInfo() const {
	LInfo info{this->player, this->name, this->isBoosted}; // Return relevant LInfo
}

void Link::reveal() {
	this->setState(LState{StateType::Reveal, this->name}); // Sets LState to Reveal
				// with the name of the link to be revealed
	this->notifyObservers(); // Notifies observers of this change to Link
}

char Link::getType() {
	return this->type;
}

int Link::getStrength() {
	return this->strength;
}
