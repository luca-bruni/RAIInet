#include "enrage.h"
#include "player.h"

Enrage::Enrage(): Ability{} {}

void Enrage::use(Link *link, Player &p) {
	if ((!(link->getInfo().isEnraged)) && (link->getType() != 'S')) { // If Link is not already Enraged or type 'S'
        	link->setEnraged(true); // Set Link to Enraged
 	      	isUsed = true;
		return;
	}
	// Throw error such that the Link is already Enraged; choose another
	// also check for nullptr in Board
	throw "Link is already enraged or Link is a server port.";
}
