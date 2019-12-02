#ifndef REM_H
#define REM_H

#include "ability.h"

// Remove deletes a virus from a Player's virus count, if above zero
class Remove: public Ability {
        public:
                Remove();
                void use(Player &p) override;
};

#endif
