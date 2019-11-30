#ifndef CELL_H
#define CELL_H

#include "board.h"
#include "subject.h"

class Cell: public Subject<Info, State> {
	Link* l; // The Link that the individual Cell contains
	int row, col; // The row and coloumn on the Board the Cell is located
	int owner; // The owner of an Ability, such as Firewall, if placed on the Cell
	bool isFW; // True if a Firewall is placed on the Cell, false otherwise
	// *** add more booleans here if a cell-based Ability is added ***

	public:
		Cell(); // Constructs a Cell object when Board is initialized
		~Cell(); // Destructs a Cell object when Board is destroyed
		void notifyObservers(); // Notifies observers the state in which Cell is
		void setLink(Link* l); // Sets piece on board and notifies observers
};

#endif
