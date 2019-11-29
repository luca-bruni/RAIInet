#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(string link1, string link2, string ability1, string ability2): out{cout}{
	links = map<char, string>();
	p1 = PlayerInfo();
	p2 = PlayerInfo();
	turn = 0;
	for(int i = 0; i < link1.length() / 2; ++i){
		char p1Name = 'a' + i;
		char p2Name = 'A' + i;
		string p1Type = link1.substr(i, i + 2);
		string p2Type = link2.substr(i, i + 2);
		links[p1Name] = p1Type;
		links[p2Name] = p2Type;
		p1.revealed.emplace_back(p1Name);
		p2.revealed.emplace_back(p2Name);
	}
	for(int i = 0; i < ability1.length(); ++i){
		p1.abilities.emplace_back(ability1[i]);
		p1.abilityUsed.emplace_back(false);
		p2.abilities.emplace_back(ability2[i]);
		p2.abilityUsed.emplace_back(false);
	}
	board = vector<vector<char>>();
	for(int r = 0; r < boardSize; ++r){
		vector<char> row = vector<char>();
		for(int c = 0; c < boardSize; ++c){
			row.emplace_back('.');
		}
		board.emplace_back(row);
	}
	for(int i = 0; i < boardSize; ++i){
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

TextDisplay::~TextDisplay(){}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
	StateType state = whoNotified.getState().state;
	int r = whoNotified.getInfo().row;
	int c = whoNotified.getInfo().col;
	if (state == StateType::Move) {
		Direction dir = whoNotified.getState().dir;
		if(dir == Direction::Up) board[r - 1][c] = board[r][c];
		else if(dir == Direction::Down) board[r + 1][c] = board[r][c];
		else if(dir == Direction::Left) board[r][c - 1] = board[r][c];
		else board[r][c + 1] = board[r][c];
		board[r][c] = '.';
	} else if(state == StateType::Reveal){
		if(whoNotified.getState().player == 0) p1.revealed.emplace_back(board[r][c]);
		else p2.revealed.emplace_back(board[r][c]);
	} else if(state == StateType::Delete) {
		board[r][c] = '.';
	} else if(state == StateType::Download){
		if(whoNotified.getState().player == 0){
			if(whoNotified.getInfo().type == 'D') ++p1.data;
			else ++p1.virus;
		} else {
			if(whoNotified.getInfo().type == 'V') ++p2.data;
			else ++p2.virus;
		}
	} else if(state == StateType::Ability){
		if(turn == 0) p1.abilityUsed[whoNotified.getState().id] == true;
		else p2.abilityUsed[whoNotified.getState().id] == true;
	} 
}

void TextDisplay::displayPlayer(int player) {
	out << "Player " << (player + 1) << ":" << endl;
	PlayerInfo &dp = (player == 0 ? p1 : p2);
	out << "Downloaded: " << dp.data << "D, " << dp.virus << "V" << endl;
	out << "Abilities: " << dp.abilities.size() << endl;
	
	PlayerInfo &p = (turn == 0 ? p1 : p2);
	char linkName = (player == 0 ? 'a' : 'A');
	for(int i = 0; i < links.size() / 2; ++i){
		out << (linkName + i) << ": ";
		char found = 'z';
		for (auto c : p.revealed) {
			if(c == (linkName + i)) found = c;
		}
		if(found == 'z') out << "?";
		else out << links[linkName+i];
		if(i == links.size() / 4 - 1) out << endl;
		else out << '\t';
	}
}

void TextDisplay::display(){
	displayPlayer(0);
	out << "========" << endl;
	for(int r = 0; r < board.size(); ++r){
		for(int c = 0; c < board[r].size(); ++c){
			out << board[r][c];
		}
		out << endl;
	}
	out << "========" << endl;
	displayPlayer(1);
}

void TextDisplay::displayAbilities(){
	PlayerInfo &p = (turn == 0 ? p1 : p2);
	for(int i = 0; i < p.abilities.size(); ++i){
		out << i << ": ";
		if(p.abilities[i] == 'L') out << "Link boost";
		else if(p.abilities[i] == 'F') out << "Firewall";
		else if(p.abilities[i] == 'D') out << "Download";
		else if(p.abilities[i] == 'P') out << "Polarize";
		else if(p.abilities[i] == 'S') out << "Scan";
		
		if(p.abilityUsed[i]) out << " - USED";
		out << endl;
	}
}
