#include "polarize.h"

Polarize::Polarize(): isUsed{false} {}

void Polarize::use(Link *link) {
    link->toggleType();
    isUsed = true;
}
