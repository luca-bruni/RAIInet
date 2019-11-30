#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(string l1, string l2, string a1, string a2): GDisplay{l1,l2,a1,a2},
								      out{cout}{}

void TextDisplay::swapTurn() {turn = (turn ? 0 : 1);}

TextDisplay::~TextDisplay(){}

void TextDisplay::displayPlayer(int player) {
	out << "Player " << (player + 1) << ":" << endl;
	PlayerInfo *dp = (player == 0 ? pi[0] : pi[1]);
	out << "Downloaded: " << dp->data << "D, " << dp->virus << "V" << endl;
	out << "Abilities: " << dp->abilities.size() << endl;
	PlayerInfo *p = (turn == 0 ? pi[0] : pi[1]);
	char linkName = (player == 0 ? 'a' : 'A');
	for(size_t i = 0; i < links.size() / 2; ++i){
		char newName = (linkName + i);
		out << newName << ": ";
		char found = 'z';
		for (auto c : p->revealed) {
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
			out << board[r][c];
		}
		out << endl;
	}
	out << "========" << endl;
	displayPlayer(1);
}

void TextDisplay::displayAbilities(){
	PlayerInfo *p = (turn == 0 ? pi[0] : pi[1]);
	for(size_t i = 0; i < p->abilities.size(); ++i){
		out << i + 1 << ": ";
		if(p->abilities[i] == 'L') out << "Link boost";
		else if(p->abilities[i] == 'F') out << "Firewall";
		else if(p->abilities[i] == 'D') out << "Download";
		else if(p->abilities[i] == 'P') out << "Polarize";
		else if(p->abilities[i] == 'S') out << "Scan";
		
		if(p->abilityUsed[i]) out << " - USED";
		out << endl;
	}
}

void TextDisplay::printError(string msg) { out << msg << endl; }
