#include "scan.h"
#include "player.h"

Scan::Scan(): Ability{} {}

void Scan::use(Link *link, Player &p) {
    link->reveal();
    isUsed = true;
}
