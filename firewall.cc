#include "firewall.h"
#include "player.h"

Firewall::Firewall(): isUsed{false} {}

void Firewall::use(Cell *cell, Player &p) {
    cell->setIsFW(true);
    isUsed = true;
}
