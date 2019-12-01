#include "cell.h"

using namespace std;

Cell::Cell(int row, int col): link{nullptr}, row{row}, col{col}, owner{0}, isFW{false} {}

void Cell::setLink(shared_ptr<Link> link) {
	this->link = link;
	this->notifyObservers();
}

shared_ptr<Link> Cell::getLink() {
	 return this->link;
}

CInfo getInfo() {
	Info i{0, this->row, this->col, this->isFW, this->owner, ' ', false};
	return i;
}
