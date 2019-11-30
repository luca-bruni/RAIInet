#ifndef SCAN_H
#define SCAN_H

#include "ability.h"

class Scan: public Ability {
	public:
		Scan();
		void use(Link *link) override;
};

#endif
