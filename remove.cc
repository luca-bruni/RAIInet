#include "remove.h"
#include "player.h"

Remove::Remove(): Ability{} {}

void Remove::use(Player &p) {
	if (p.getVirus()) { // If Player's virus count is not zero
    		p.removeVirus(); // Removes one virus
    		isUsed = true;
		return;
	}
	// Throw error that Player cannot have negative viruse
	throw "Virus count is already at zero.";
}
