#include "scan.h"

Scan::Scan(): isUsed{false} {}

void Scan::use(Link *link) {
    link->reveal();
    isUsed = true;
}
