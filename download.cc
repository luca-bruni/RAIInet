#include "download.h"
#include "player.h"
  
Download::Download(): isUsed{false} {}

void Download::use(Link *link, Player &p) {
    if (link->getType() == 'V') p.addVirus();
    else p.addData();
    isUsed = true;
}
