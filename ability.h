#ifndef ABILITY_H
#define ABILITY_H

#include "cell.h"
#include "link.h"

class Ability {
	public:
		bool isUsed;
		virtual void use(Cell *cell) = 0;
		virtual void use(Link *link) = 0;
}

#endif
