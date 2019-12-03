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

class Player : public Subject<PInfo, PState> {
    int dataDownloaded = 0;
    int virusDownloaded = 0;
    std::vector<std::unique_ptr<Ability>> abilities;
    int id;
public:
    Player(std::string abs, int id);
    ~Player();
    void useAbility(int choice, Cell *cell);
    void useAbility(int choice, Link *link);
    void useAbility(int choice);
    void download(std::shared_ptr<Link> link);
    int getVirus();
    int getData();
    void addVirus();
    void removeVirus();
    void addData();
    PInfo getInfo() const override;
};
#endif
