#include "cell.h"

using namespace std;

Cell::Cell(int row, int col): link{nullptr}, row{row}, col{col}, owner{0}, isFW{false} {}

void Cell::setLink(shared_ptr<Link> link) {
	this->link = link;
	this->setState(CState{StateType::CellChange, this->link->getInfo().link});
	this->notifyObservers();
}

shared_ptr<Link> Cell::getLink() {
	 return this->link;
}

void Cell::setFirewall(int player) {
	this->owner = player;
	this->setState(CState{StateType::CellChange, 'F'});
	isFW = true;
	this->notifyObservers();
}

CInfo getInfo() const {
	CInfo info{this->row, this->col, '.', this->isFW, this->owner};
	if (!(this->link)) { info.link = this->link->getInfo().link; }
	return info;
}
