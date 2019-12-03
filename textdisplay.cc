#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(string l1, string l2, string a1, string a2): GDisplay{l1,l2,a1,a2},
								      out{cout}{}

void TextDisplay::swapTurn() {turn = (turn ? 0 : 1);}

TextDisplay::~TextDisplay(){}

void TextDisplay::displayPlayer(int player) {
	out << "Player " << (player + 1) << ":" << endl;
	out << "Downloaded: "<< pi[player]->data << "D, "<< pi[player]->virus << "V" << endl;
	int abilities = 0;
	for (size_t i = 0; i < pi[player]->abilities.size(); ++i) {
		if(!pi[player]->abilityUsed[i]) ++abilities;
	}
	out << "Abilities: "<< abilities << endl;
	char linkName = (player == 0 ? 'a' : 'A');
	for(size_t i = 0; i < links.size() / 2; ++i){
		char newName = (linkName + i);
		out << newName << ": ";
		char found = 'z';
		for (auto c : pi[turn]->revealed) {
			if(c == newName) found = c;
		}
		if(found == 'z') out << "?";
		else out << links[newName];
		if(i == links.size() / 4 - 1) out << endl;
		else out << '\t';
	}
	out << endl;
}

void TextDisplay::display(){
	displayPlayer(0);
	out << "========" << endl;
	for(size_t r = 0; r < board.size(); ++r){
		for(size_t c = 0; c < board[r].size(); ++c){
			try {
				if(board[r][c] != '.'){
					out << board[r][c];
				} else if(firewalls.at(make_pair(r, c))){
					out << 'm';
				} else {
					out << 'w';
				}
			} catch (out_of_range e) {
				out << board[r][c];
			}
		}
		out << endl;
	}
	out << "========" << endl;
	displayPlayer(1);
}

void TextDisplay::displayAbilities(){
	for(size_t i = 0; i < pi[turn]->abilities.size(); ++i){
		out << i + 1 << ": ";
		if(pi[turn]->abilities[i] == 'L') out << "Link boost";
		else if(pi[turn]->abilities[i] == 'F') out << "Firewall";
		else if(pi[turn]->abilities[i] == 'D') out << "Download";
		else if(pi[turn]->abilities[i] == 'P') out << "Polarize";
		else if(pi[turn]->abilities[i] == 'S') out << "Scan";
		else if(pi[turn]->abilities[i] == 'E') out << "Enrage";
		else if(pi[turn]->abilities[i] == 'R') out << "Remove";
		else if(pi[turn]->abilities[i] == 'B') out << "Buff";
		
		if(pi[turn]->abilityUsed[i]) out << " - USED";
		out << endl;
	}
}

void TextDisplay::printMsg(string msg) { out << msg << endl; }
