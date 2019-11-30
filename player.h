#ifndef PLAY_H
#define PLAY_H
#include <vector>
#include "ability.h"
#include "linkboost.h"
#include "firewall.h"
#include "download.h"
#include "polarize.h"
#include "scan.h"
#include "link.h"
#include "cell.h"

class Player {
    int dataDownloaded = 0;
    int virusDownloaded = 0;
    std::vector<Ability*> abilities;
public:
    Player(std::vector<char> &abs);
    ~Player();
    void useAbility(int choice, Cell *cell);
    void useAbility(int choice, Link *link);
    void download(Link *link);
    int getVirus();
    int getData();
    void addVirus();
    void addData();
};
#endif
