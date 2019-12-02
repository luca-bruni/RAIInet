#include "scan.h"
#include "player.h"

Scan::Scan(): Ability{} {}

void Scan::use(Link *link, Player &p) {
	if (link->getType() != 'S') { // or nullptr
		link->reveal();
		isUsed = true;
		return;
	}
	// throw an error otherwise
	throw "Cannot scan a server port.";
}
