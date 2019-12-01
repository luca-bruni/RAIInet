#include "cell.h"

using namespace std;

Cell::Cell(int row, int col): row{row}, col{col}, link{nullptr}, isFW{false} {

}

Cell::~Cell() {

}

void Cell::notifyObservers() {

}

void Cell::setLink(Link* l) {

}
