#include "scan.h"
#include "player.h"

Scan::Scan(): isUsed{false} {}

void Scan::use(Link *link, Player &p) {
    link->reveal();
    isUsed = true;
}
