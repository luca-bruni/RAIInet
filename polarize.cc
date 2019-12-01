#include "polarize.h"
#include "player.h"

Polarize::Polarize(): Ability{} {}

void Polarize::use(Link *link, Player &p) {
	link->setType((link->getType() == 'V' ? 'D' : 'V'));
    	isUsed = true;
}
