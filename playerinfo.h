#ifndef PINFO_H
#define PINFO_H

#include <vector>

struct PlayerInfo {
	int data, virus;
	std::vector<char> revealed;
	std::vector<char> abilities;
	std::vector<bool> abilityUsed;
	PlayerInfo(): data{0}, virus{0}, revealed{std::vector<char>()},
			abilities{std::vector<char>()}, abilityUsed{std::vector<bool>()}{}
};

#endif
