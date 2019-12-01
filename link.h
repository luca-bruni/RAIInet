#ifndef LINK_H
#define LINK_H

#include "subject.h"
#include "info.h"
#include "state.h"
#include "observer.h"

class Link : public Subject<LInfo, LState> {
	char name; // Name of the Link
	char type; // Type of the Link (data, virus, server port)
	int strength; // Strength of the Link (from 1-4)
	int player; // Owner of the Link; who placed the Link
	bool isBoosted; // True if LinkBoost ability used on this Link, false otherwise
	public:
		Link(char name, char type, int strength, int player); // Link constructor
		LInfo getInfo() const override; // Retrieves all field data of Link
		void reveal(); // Notifies observers that piece is revealed to players
		char getType(); // Returns the type field of the Link
		int getStrength(); // Returns the strength field of the Link
};

#endif
