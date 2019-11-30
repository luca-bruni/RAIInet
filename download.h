#ifndef DOWN_H
#define DOWN_H

#include "ability.h"

class Download: public Ability {
	public:
		Download();
		void use(Link *link, Player &p) override;
};

#endif
