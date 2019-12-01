#include "linkboost.h"
#include "player.h"

LinkBoost::LinkBoost(): Ability{} {}

void LinkBoost::use(Link *link, Player &p) {
    link->setBoosted(true);
    isUsed = true;
}
