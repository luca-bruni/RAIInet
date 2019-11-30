#include "controller.h"

using namespace std;

Controller::Controller(string l1, string l2, string a1, string a2, bool graphics):
			l1{l1}, l2{l2}, a1{a1}, a2{a2}, graphics{graphics}{
	if(l1 == "") this->l1 = initLinks;
	if(l2 == "") this->l2 = initLinks;
	if(a1 == "") this->a1 = initAbilities;
	if(a2 == "") this->a2 = initAbilities;
}

void Controller::startGame(){
	TextDisplay *td = new TextDisplay(l1, l2, a1, a2);
	td->display();
	td->displayAbilities();
	td->swapTurn();
	td->display();
	td->displayAbilities();
	delete td;
	GraphicsDisplay *gd = new GraphicsDisplay(l1, l2, a1, a2);
	gd->display();
	char cmd;
	while(true) {
		cin >> cmd;
		if(cmd == 'q') {
			break;
		}
		if(cmd == 's') {
			gd->swapTurn();
			gd->display();
		}
	}
	delete gd;
}
