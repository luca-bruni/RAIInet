#include "firewall.h"
#include "player.h"

Firewall::Firewall(): Ability{} {}

void Firewall::use(Cell *cell, Player &p) {
	if ((Cell->getInfo() != 'D') && (Cell->getInfo() != 'V') && (Cell->getInfo() != 'S')) {
		cell->setFirewall(p.getInfo().player);
		isUsed = true;
		return;
	}
	throw "Cannot place Firewall on a non-empty Cell.";
}
