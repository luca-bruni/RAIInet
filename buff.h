#ifndef BUFF_H
#define BUFF_H

#include "ability.h"

// Buff increases a Link's strength by 1; potentially useful in battles
class Buff: public Ability {
        public:
                Buff();
                void use(Link *link, Player &p) override;
};

#endif
