#ifndef LINK_H
#define LINK_H

#include "subject.h"
#include "info.h"
#include "state.h"

class Link : public Subject<LInfo, LState> {
	char name;
	char type;
	int strength;
	int player;
	bool isBoosted;
	public:
		Link(char name, char type, int strength, int player);
		LInfo getInfo() const override;
		void reveal();
		int getType();
		int getStrength();
};

#endif
