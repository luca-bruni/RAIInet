#ifndef PLAY_H
#define PLAY_H
#include <vector>
#include <string>
#include <memory>
#include "ability.h"
#include "linkboost.h"
#include "firewall.h"
#include "download.h"
#include "polarize.h"
#include "scan.h"
#include "link.h"
#include "cell.h"
#include "observer.h"
#include "info.h"
#include "state.h"

class Player : public Subject<Info, State> {
    int dataDownloaded = 0;
    int virusDownloaded = 0;
    std::vector<Ability*> abilities;
public:
    Player(std::string abs);
    ~Player();
    void useAbility(int choice, Cell *cell);
    void useAbility(int choice, Link *link);
    void download(std::shared_ptr<Link> link);
    int getVirus();
    int getData();
    void addVirus();
    void addData();
    Info getInfo() const override;
};
#endif
