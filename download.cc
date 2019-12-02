#include "download.h"
#include "player.h"
  
Download::Download(): Ability{} {}

void Download::use(Link *link, Player &p) {
	if (link->getType() == 'S') {
		// Throw an error such that the link must not be a server port
		// also check for nullptr in Board
		throw "Cannot download a server port.";
	}
	if (link->getType() == 'V') p.addVirus();
	else p.addData();
	isUsed = true;
}
