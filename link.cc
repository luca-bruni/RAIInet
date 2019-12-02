#include "link.h"

using namespace std;

Link::Link(char name, char type, int strength, int player): name{name}, type{type},
			strength{strength}, player{player}, isBoosted{false} {}

LInfo Link::getInfo() const {
	// Return relevant LInfo
	return LInfo {this->player, this->name, this->isBoosted};
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
