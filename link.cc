#include "link.h"

using namespace std;

Link::Link(char name, char type, int strength, int player): name{name}, type{type},
			strength{strength}, player{player}, isBoosted{false} {}

LInfo Link::getInfo() const {
	LInfo info{this->player, this->name, this->isBoosted};
}

void Link::reveal() {
	this->setState(LState{StateType::Reveal, this->name});
	this->notifyObservers();	
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
