#include "player.h"

using namespace std;

Player::Player(string abs, int id): abilities{vector<unique_ptr<Ability>>()}, id{id} {
    for (size_t i = 0; i < abs.length(); ++i) {
        if (abs[i] == 'L') abilities.emplace_back(unique_ptr<LinkBoost>());
        else if (abs[i] == 'F') abilities.emplace_back(unique_ptr<Firewall>());
        else if (abs[i] == 'D') abilities.emplace_back(unique_ptr<Download>());
        else if (abs[i] == 'P') abilities.emplace_back(unique_ptr<Polarize>());
        else if (abs[i] == 'S') abilities.emplace_back(unique_ptr<Scan>());
    }
}

Player::~Player() {}

void Player::useAbility(int choice, Cell *cell) {
    if (!abilities[choice-1]->isUsed) {
        abilities[choice-1]->use(cell, *this);
    }
    this->setState(PState{StateType::Ability, choice - 1, '.'});
    this->notifyObservers();
}

void Player::useAbility(int choice, Link *link) {
    if (!abilities[choice-1]->isUsed) {
        abilities[choice-1]->use(link, *this);
    }
    this->setState(PState{StateType::Ability, choice - 1, link->getType()});
    this->notifyObservers();
}

void Player::download(shared_ptr<Link> link) {
    if (link->getType() == 'V') virusDownloaded++;
    else dataDownloaded++;
    this->setState(PState{StateType::Download, 0, link->getType()});
    this->notifyObservers();
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

void Player::removeVirus() {
    virusDownloaded--;
}

void Player::addData() {
    dataDownloaded++;
}

PInfo Player::getInfo() const {
    return PInfo {this->id};   
}
