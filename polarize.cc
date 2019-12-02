#include "polarize.h"
#include "player.h"

Polarize::Polarize(): Ability{} {}

void Polarize::use(Link *link, Player &p) {
	if (link->getType() != 'S') { // If Link is not a server port
		link->setType((link->getType() == 'V' ? 'D' : 'V')); // Polarize
    		isUsed = true;
	}
	// Throw error if server port or nullptr
	throw "Cannot Polarize a server port.";
}
