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

class Controller {
	const std::string initLinks = "V1V2V3V4D1D2D3D4";
	const std::string initAbilities = "LFDSP";
	std::string l1, l2;
	std::string a1, a2;
	bool graphics;
	std::vector<std::unique_ptr<GDisplay>> displays;
	Board board;
	public:
		Controller(std::string l1, std::string l2, std::string a1, 
					   std::string a2, bool graphics=false);
		void startGame();
		void loop(std::istream &in);
};

#endif
