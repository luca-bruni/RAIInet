#ifndef ABILITY_H
#define ABILITY_H

#include "cell.h"
#include "link.h"

class Player;

class Ability {
	public:
		bool isUsed;
		Ability(): isUsed{false} {}
		virtual void use(Cell *cell, Player &p) = 0;
		virtual void use(Link *link, Player &p) = 0;
};

#endif
