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
	istream& in = cin;
	vector<unique_ptr<GDisplay>> displays = vector<unique_ptr<GDisplay>>();
	displays.emplace_back(make_unique<TextDisplay>(l1, l2, a1, a2));
	if(graphics) displays.emplace_back(make_unique<GraphicsDisplay>(l1, l2, a1, a2));
	
	for(int i = 0; i < displays.size(); ++i) displays[i]->display();

	string cmd;
	while(true) {
		in >> cmd;
		if(cmd == "move") {
			char c;
			if(!(in >> c)) {
				displays[0]->printError("move needs a character respresentation for a piece to move.");
			} else {
				string dir;
				in >> dir;
				try {
					// MOVE PIECE
				} catch (...) {}
			}
		} else if(cmd == "abilities") {
			for(int i = 0; i < displays.size(); ++i)
				displays[i]->displayAbilities();
		} else if(cmd == "ability") {
			int id;
			if(!(in >> id)) {
				displays[0]->printError("ability needs an ID for the card to use.");
			} else {
				try {
					// USE ABILITY
				} catch (...) {}
			}
		} else if(cmd == "board") {
			for(int i = 0; i < displays.size(); ++i) displays[0]->display();
		} else if(cmd == "sequence") {
			// SWITCH THE IN STREAM
			// but can't do that normally since the in stream is a reference
			// hence its constant...
		} else if(cmd == "quit") {
			break;
		}
	}
}
