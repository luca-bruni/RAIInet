#include "cell.h"
#include <iostream>

using namespace std;

Cell::Cell(int row, int col): link{nullptr}, row{row}, col{col}, owner{0}, isFW{false} {}

void Cell::setLink(shared_ptr<Link> link) {
	this->link = link; // Mutates this' link to the passed in link
	// Updates CState to CellChange, with new Link's name
	if(!link.get()) this->setState(CState{StateType::CellChange, '.'});
	else {
		this->setState(CState{StateType::CellChange, this->link->getInfo().link});
		cout << this->link->getInfo().link << endl;
	}
	this->notifyObservers(); // Notifies observers of the change to Cell
}

shared_ptr<Link> Cell::getLink() {
	 return this->link;
}

void Cell::setFirewall(int player) {
	this->owner = player; // Sets owner of the Cell to the player placing Firewall
			      // The owner field is only used to determine who placed
	this->setState(CState{StateType::CellChange, 'F'}); // Updates CState to
			      // CellChange, with the F char for Firewall
	isFW = true; // Sets isFW to true since a Firewall now exists on the Cell
	this->notifyObservers(); // Notifies observers of the change to Cell
}

CInfo Cell::getInfo() const {
	CInfo info{this->row, this->col, '.', this->isFW, this->owner};
	if (!(this->link)) { info.link = this->link->getInfo().link; } // If Link is
			      // not nullptr, set link in CInfo to the Link's name
	return info;
}
