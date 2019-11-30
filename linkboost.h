#ifndef BOOST_H
#define BOOST_H

#include "ability.h"

class LinkBoost: public Ability {
	public:
		LinkBoost();
		void use(Link *link, Player &p) override;
};

#endif
