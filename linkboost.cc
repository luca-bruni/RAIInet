#include "linkboost.h"

LinkBoost::LinkBoost(): isUsed{false} {}

void LinkBoost::use(Link *link, Player &p) {
    link->setBoosted(true);
    isUsed = true;
}
