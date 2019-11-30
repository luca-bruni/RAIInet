#include "linkboost.h"

LinkBoost::LinkBoost(): isUsed{false} {}

void LinkBoost::use(Link *link) {
    link->setBoosted(true);
    isUsed = true;
}