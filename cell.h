#ifndef CELL_H
#define CELL_H

#include "board.h"
#include "subject.h"
#include "state.h"
#include "info.h"
#include "link.h"
#include <memory>

class Cell: public Subject<CInfo, CState> {
	std::shared_ptr<Link> link; // The Link that the individual Cell contains
	int row, col; // The row and coloumn on the Board the Cell is located
	int owner; // The owner of an Ability, such as Firewall, if placed on the Cell
	bool isFW; // True if a Firewall is placed on the Cell, false otherwise
	// *** add more booleans here if a cell-based Ability is added ***

	public:
		Cell(int row, int col); // Constructs a Cell object when Board is initialized
		void setLink(std::shared_ptr<Link> link); // Sets piece on board and notifies
	       					          // observers
		void setFirewall(int player);
		std::shared_ptr<Link> getLink(); // Returns Link in Cell
		CInfo getInfo() const override; // Retrieves all necessary info about the Cell
};

#endif
