#include "download.h"
#include "player.h"
  
Download::Download(): Ability{} {}

void Download::use(Link *link, Player &p) {
    if (link->getType() == 'V') p.addVirus();
    else p.addData();
    isUsed = true;
}
