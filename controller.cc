#include "controller.h"

using namespace std;

void Controller::loop(){
	TextDisplay *td = new TextDisplay("V1V2V3V4D1D2D3D4", "V1D2V3D4D1V2D3V4", "LFDSP", "DFLPS");
	td->display();
	td->displayAbilities();
	td->swapTurn();
	td->display();
	td->displayAbilities();
	delete td;
}
