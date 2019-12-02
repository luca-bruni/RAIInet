#include "buff.h"
#include "player.h"

Buff::Buff(): Ability{} {}

void Buff::use(Link *link, Player &p) {
        if (link->getStrength() < 4) { // If strength is within valid range
                if (link->getType() != 'S') { // or nullptr
                        link->addStrength(); // Adds to strength of the Link
                        isUsed = true;
                        return;
                }
        }
        // Throw an error such that the strength must be within valid range or Link cannot be server port
        // also check for nullptr as Link in Board
	throw "Link's strength is max, or Link is a server port.";
}
