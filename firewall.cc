#include "firewall.h"
#include "player.h"

Firewall::Firewall(): Ability{} {}

void Firewall::use(Cell *cell, Player &p) {
	if (cell->getInfo().link == '.') {
		cell->setFirewall(p.getInfo().player);
		isUsed = true;
		return;
	}
	throw "Cannot place Firewall on a non-empty Cell.";
}
