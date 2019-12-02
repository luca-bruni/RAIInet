#include "linkboost.h"
#include "player.h"

LinkBoost::LinkBoost(): Ability{} {}

void LinkBoost::use(Link *link, Player &p) {
	if (!(link->getInfo().isBoosted)) { // If Link is not already boosted
		if (link->getType() != 'S') {
			link->setBoosted(true); // Sets Link to boosted
			isUsed = true;
			return;
		}
	}
	// Throw an error such that the boosted link or server port cannot be boosted
	// also check for nullptr as Link in Board
	throw "Link already boosted or is a server port.";
}
