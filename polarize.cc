#include "polarize.h"

Polarize::Polarize(): isUsed{false} {}

void Polarize::use(Link *link, Player &p) {
    link->toggleType();
    isUsed = true;
}
