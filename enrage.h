#ifndef ENRG_H
#define ENRG_H

#include "ability.h"

// Enrage is an Ability that can be used on a Link such that the Link will always win in
// 	a battle unless the opposing Link is also Enraged. If this is the case, battle
// 	commences as normal.
class Enrage: public Ability {
        public:
                Enrage(); // Constructor
                void use(Link *link, Player &p) override; // Uses Ability on desired Link
};

#endif
