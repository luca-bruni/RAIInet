#include "controller.h"

using namespace std;

Controller::Controller(string l1, string l2, string a1, string a2, bool graphics):
			l1{l1}, l2{l2}, a1{a1}, a2{a2}, graphics{graphics}{
	if(l1 == "") this->l1 = initLinks; // Initial Links Player 1
	if(l2 == "") this->l2 = initLinks; // Initial Links Player 2
	if(a1 == "") this->a1 = initAbilities; // Initial Abilities Player 1
	if(a2 == "") this->a2 = initAbilities; // Initial Abilities Player 2
}

void Controller::startGame(){
	displays = vector<shared_ptr<GDisplay>>(); // Constructs a display pointer
	displays.emplace_back(make_shared<TextDisplay>(l1, l2, a1, a2)); // Adds a Textdisplay object to displays
	if(graphics) displays.emplace_back(make_shared<GraphicsDisplay>(l1, l2, a1, a2)); // Adds a Graphicsdisplay object to displays
	try {
		board.init(l1, l2, a1, a2, displays); // Initializes Board
	} catch(char const *s){
		string msg(s);
		for(auto d : displays) d->printMsg(msg);
		return;
	}
	for(size_t i = 0; i < displays.size(); ++i) displays[i]->display(); // Calls display on each display
	loop(cin); // Begins input loop
}

void Controller::loop(istream &in){
	string cmd; // To be read in
        while(in >> cmd) { // Each keyword typed
                if(cmd == "move") { // If command is 'move'
                        char c; // Link
                        if(!(in >> c)) { // Invalid input: not a char
                        	displays[0]->printMsg("Move needs a character respresentation for a piece to move."); // Error msg
                        } else { // If valid input: char
                                string dir; // Direction
                                in >> dir; // Reads in a direction
                                try {
                                        board.move(c, dir); // Moves the Link in specified direction
					for(auto d : displays) d->display(); // Updates displays
                                } catch (char const *s) { // Invalid dir
                                        string msg(s);
					displays[0]->printMsg(msg); // Error msg as per display
                                }
                        }
                } else if(cmd == "abilities") { // If command is 'abilities'
                        for(auto d : displays) d->displayAbilities(); // Lists abilities
                } else if(cmd == "ability") { // If command is 'ability'
                        int id; // Ability ID
                        if(!(in >> id)) { // If invalid input: not an int
                                displays[0]->printMsg("ability needs an ID for the card to use."); // Error msg
                        } else { // If valid input: int
                                //STILL CHECK FOR ERRORS
				try{
					string line;
					getline(in, line);
					if(line.size() == 0) board.useAbility(id);
					istringstream iss{line};
					int row;
                                	if(iss >> row) {
						int col;
						if(!(iss >> col)) {
							displays[0]->printMsg("Incorrect use of card.");
							continue;
						}
                                        	board.useAbility(id, row, col); // If Cell-ability, use on that Cell
					} else {
						iss.clear();
					}
					char link;
                                	if(iss >> link){ // If Link name read in:
                                        	board.useAbility(id, link); // Use on that Link
                                	}
				} catch (char const *s) {
					string msg{s};
					displays[0]->printMsg(msg);
				}
                        }
                } else if(cmd == "board") { // If command is 'board'
                        for(auto d : displays) d->display(); // Displays board
                } else if(cmd == "sequence") { // If command is 'sequence'
			string file; // Filename to read in for sequence
			in >> file; // Reads in a filename
                        ifstream is{file}; // Converts file to file type
			loop(is); // Commences game loop but with the contents of the file
                	break;
		} else if(cmd == "quit") { // If command 'quit'
                        break; // Breaks out of game loop
                }

		if(board.hasWon()){
			int winner = board.whoWon();
			if(winner){
				for(auto d : displays) d->printMsg("PLAYER 2 WINS!");
			} else {
				for(auto d : displays) d->printMsg("PLAYER 1 WINS!");
			}
			break;
		}
        }
}
