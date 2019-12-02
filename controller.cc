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
	displays = vector<GDisplay*>();
	displays.emplace_back(new TextDisplay(l1, l2, a1, a2));
	if(graphics) displays.emplace_back(new GraphicsDisplay(l1, l2, a1, a2));

	for(int i = 0; i < displays.size(); ++i) displays[i]->display();

	board.init(l1, l2, a1, a2, displays);
	loop(cin);
}

void Controller::loop(istream &in){
	string cmd;
        while(in >> cmd) {
                if(cmd == "move") {
                        char c;
                        if(!(in >> c)) {
                        	displays[0]->printError("move needs a character respresentation for a piece to move.");
                        } else {
                                string dir;
                                in >> dir;
                                try {
                                        board.move(c, dir);
					for(auto d : displays) d->display();
                                } catch (...) {
                                        displays[0]->printError("Invalid move.");
                                }
                        }
                } else if(cmd == "abilities") {
                        for(auto d : displays) d->displayAbilities();
                } else if(cmd == "ability") {
                        int id;
                        if(!(in >> id)) {
                                displays[0]->printError("ability needs an ID for the card to use.");
                        } else {
                                //STILL CHECK FOR ERRORS
                                int row;
                                char link;
                                if(cin >> row) {
                                        int col;
                                        cin >> col;
                                        board.useAbility(id, row, col);
                                } else if(cin >> link){
                                        board.useAbility(id, link);
                                }
                        }
                } else if(cmd == "board") {
                        for(auto d : displays) d->display();
                } else if(cmd == "sequence") {
			string file;
			in >> file;
                        ifstream is{file};
			loop(is);
                } else if(cmd == "quit") {
                        break;
                }
        }

}
