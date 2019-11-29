#ifndef TEXT_H
#define TEXT_H

#include "observer.h"
#include "subject.h"
#include "state.h"
#include "info.h"
#include "player.h"
#include "playerinfo.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

class TextDisplay: public Observer<Info, State> {
	const size_t boardSize = 8;
	const size_t abilitySize = 5;
	std::ostream &out;
	std::vector<std::vector<char>> board;
	std::map<char, std::string> links;
	PlayerInfo *p1;
	PlayerInfo *p2;
	int turn;
	void displayPlayer(int player);
	public:
		void swapTurn(); // TESTING ONLY
		TextDisplay(std::string link1, std::string link2, std::string ability1,
				std::string ability2);
		~TextDisplay();
		void notify(Subject<Info, State> &whoNotified) override;
		void display();
		void displayAbilities();
};

#endif
