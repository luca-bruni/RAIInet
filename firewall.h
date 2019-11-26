#ifndef FIRE_H
#define FIRE_H

#include "ability.h"

class Firewall: public Ability {
	public:
		Firewall();
		void use(Cell *cell) override;
}

#endif
