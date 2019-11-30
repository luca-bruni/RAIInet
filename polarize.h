#ifndef POLAR_H
#define POLAR_H

#include "ability.h"

class Polarize: public Ability {
	public:
		Polarize();
		void use(Link *link) override;
};

#endif
