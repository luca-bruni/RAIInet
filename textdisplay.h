#ifndef TEXT_H
#define TEXT_H

<<<<<<< HEAD
#include "display.h"
=======
#include "observer.h"
#include "subject.h"
#include "state.h"
#include "info.h"
#include "playerinfo.h"
>>>>>>> 70ce400d8eb751dcb303f511172fdcce76a51c4a
#include <iostream>

class TextDisplay: public GDisplay {
	std::ostream &out;
	protected:
		void displayPlayer(int player) override;
	public:
		void swapTurn();
		TextDisplay(std::string l1, std::string l2, std::string a1, std::string a2);
		~TextDisplay();
		void display() override;
		void displayAbilities() override;
};

#endif
