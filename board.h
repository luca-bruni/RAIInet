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
	const int boardSize = 8; // Default size of the board; length and width
	const int handSize = 5; // Default size of a Player's hand
	std::vector<std::vector<Cell>> board; // 2-D array of Cell 
	std::vector<std::unique_ptr<Player>> players; // Array of Players
	std::map<char, std::shared_ptr<Link>> links; // Existing Link keys
	int turn; // Determines which Player is moving now
	public:
		Board(); // Constructs a Board
		// Initializes board to game-start
		void init(std::string l1, std::string l2, std::string a1, std::string a2,
				std::vector<std::shared_ptr<GDisplay>> &displays);
		void setDisplay(GDisplay *d); // Allows displays to observe all necessary Subjects
		bool hasWon(); // Checks state of Board for a winning state
		int whoWon(); // Identifies which Player won
		void move(char link, std::string dir); // To move an existing piece
		void battle(Cell &origin, Cell &dest); // Commences a RAIInet battle
		void useAbility(int id, char link); // Ability on a Link
		void useAbility(int id, int row, int col); // Ability on a Cell
		void useAbility(int id); // Ability on self
};

#endif
