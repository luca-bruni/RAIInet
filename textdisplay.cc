#include "textdisplay.h"

using namespace std;

void TextDisplay::swapTurn() {turn = (turn ? 0 : 1);}

TextDisplay::TextDisplay(string link1, string link2, string ability1, string ability2): out{cout}{
	links = map<char, string>();
	p1 = new PlayerInfo();
	p2 = new PlayerInfo();
	turn = 0;
	for(size_t i = 0; i < link1.length() / 2; ++i){
		char p1Name = 'a' + i;
		char p2Name = 'A' + i;
		string p1Type = link1.substr(i * 2, 2);
		string p2Type = link2.substr(i * 2, 2);
		links[p1Name] = p1Type;
		links[p2Name] = p2Type;
		p1->revealed.emplace_back(p1Name);
		p2->revealed.emplace_back(p2Name);
	}
	for(size_t i = 0; i < ability1.length(); ++i){
		p1->abilities.emplace_back(ability1[i]);
		p1->abilityUsed.emplace_back(false);
		p2->abilities.emplace_back(ability2[i]);
		p2->abilityUsed.emplace_back(false);
	}
	board = vector<vector<char>>();
	for(size_t r = 0; r < boardSize; ++r){
		vector<char> row = vector<char>();
		for(size_t c = 0; c < boardSize; ++c){
			row.emplace_back('.');
		}
		board.emplace_back(row);
	}
	for(size_t i = 0; i < boardSize; ++i){
		char p1 = 'a' + i;
		char p2 = 'A' + i;
		if(i == boardSize / 2 - 1 || i == boardSize / 2) {
			board[0][i] = 'S';
			board[boardSize - 1][i] = 'S';
			board[1][i] = p1;
			board[boardSize - 2][i] = p2;
		} else {
			board[0][i] = p1;
			board[boardSize - 1][i] = p2;
		}
	}
}

TextDisplay::~TextDisplay(){
	delete p1;
	delete p2;
}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
	const State& state = whoNotified.getState();
	int r = whoNotified.getInfo().row;
	int c = whoNotified.getInfo().col;
	if (state.state == StateType::CellChange) {
		board[r][c] = whoNotified.getInfo().link;
		if(whoNotified.getInfo().link == '.' && whoNotified.getInfo().firewall){
			if(whoNotified.getInfo().playerFirewall) board[r][c] = 'w';
			else board[r][c] = 'm';
		}
		turn = (turn ? 0 : 1);
	} else if(state.state == StateType::Reveal){
		p1->revealed.emplace_back(whoNotified.getInfo().link);
		p2->revealed.emplace_back(whoNotified.getInfo().link);
	} else if(state.state == StateType::Download){
		if(state.player == 0){
			if(links[whoNotified.getInfo().link][0] == 'D') ++p1->data;
			else ++p1->virus;
		} else {
			if(links[whoNotified.getInfo().link][0] == 'V') ++p2->data;
			else ++p2->virus;
		}
	} else if(state.state == StateType::Ability){
		if(turn == 0) p1->abilityUsed[state.id] = true;
		else p2->abilityUsed[state.id] = true;
	} 
}

void TextDisplay::displayPlayer(int player) {
	out << "Player " << (player + 1) << ":" << endl;
	PlayerInfo *dp = (player == 0 ? p1 : p2);
	out << "Downloaded: " << dp->data << "D, " << dp->virus << "V" << endl;
	out << "Abilities: " << dp->abilities.size() << endl;
	PlayerInfo *p = (turn == 0 ? p1 : p2);
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
	PlayerInfo *p = (turn == 0 ? p1 : p2);
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
