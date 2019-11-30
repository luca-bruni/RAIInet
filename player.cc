#include "player.h"
using namespace std;

Player::Player(vector<char> &abs): abilities{vector<Ability*>()} {
    for (size_t i = 0; i < abs.size(); ++i) {
        if (abs[i] == 'L') abilities.emplace_back(new LinkBoost());
        else if (abs[i] == 'F') abilities.emplace_back(new Firewall());
        else if (abs[i] == 'D') abilities.emplace_back(new Download());
        else if (abs[i] == 'P') abilities.emplace_back(new Polarize());
        else if (abs[i] == 'S') abilities.emplace_back(new Scan());
    }
}

Player::~Player() {
    for (size_t i = 0; i < abilities.size(); ++i) {
        delete abs[i];
    }
}

void Player::useAbility(int choice, Cell *cell) {
    if (!abilities[choice-1]->isUsed) {
        abilities[choice-1]->use(cell, *this);
    }
}

void Player::useAbility(int choice, Link *link) {
    if (!abilities[choice-1]->isUsed) {
        abilities[choice-1]->use(link, *this);
    }
}

void Player::download(Link *link) {
    if (link->getType() == 'V') virusDownloaded++;
    else dataDownloaded++;
}

int Player::getVirus() { 
    return virusDownloaded;
}

int Player::getData() {
    return dataDownloaded;
}

void Player::addVirus() {
    virusDownloaded++;
}

void Player::addData() {
    dataDownloaded++;
}
