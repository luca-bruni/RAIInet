#ifndef CON_H
#define CON_H

#include "display.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>

class Controller {
	const std::string initLinks = "V1V2V3V4D1D2D3D4"; // Default eight Links
	const std::string initAbilities = "LFDSP"; // Default five Abilities
	std::string l1, l2; // Links of Player 1, 2
	std::string a1, a2; // Abilities of Player 1, 2
	bool graphics; // True if user wants graphics to be displayed; false otherwise
	std::vector<std::shared_ptr<GDisplay>> displays; // Display array
	Board board; // The Board
	public:
		Controller(std::string l1, std::string l2, std::string a1, 
					   std::string a2, bool graphics=false); // Controller constructor
		void startGame(); // Method to begin the game
		void loop(std::istream &in); // Method to loop game commands
};

#endif
