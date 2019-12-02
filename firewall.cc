#include "firewall.h"
#include "player.h"

Firewall::Firewall(): Ability{} {}

void Firewall::use(Cell *cell, Player &p) {
    cell->setFirewall(p.getInfo().player);
    isUsed = true;
}
