#ifndef TEXT_H
#define TEXT_H

#include "display.h"
#include <iostream>

class TextDisplay: public GDisplay {
	std::ostream &out;
	protected:
		void displayPlayer(int player) override;
	public:
		void swapTurn(); // TESTING ONLY
		TextDisplay(std::string l1, std::string l2, std::string a1, std::string a2);
		~TextDisplay();
		void display() override;
		void displayAbilities() override;
};

#endif
