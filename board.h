#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "player.h"
#include "display.h"
#include "link.h"
#include <vector>
#include <map>
#include <string>
#include <memory>

class Board {
	const int boardSize = 8;
	const int handSize = 5;
	std::vector<std::vector<Cell>> board;
	std::vector<std::unique_ptr<Player>> players;
	std::map<char, std::shared_ptr<Link>> links;
	int turn;
	public:
		Board();
		void init(std::string l1, std::string l2, std::string a1, std::string a2,
				std::vector<GDisplay*> &displays);
		void setDisplay(GDisplay *d);
		bool hasWon();
		int whoWon();
		void move(char link, std::string dir);
		void battle(Cell &origin, Cell &dest);
		void useAbility(int id, char link);
		void useAbility(int id, int row, int col);
};

#endif
