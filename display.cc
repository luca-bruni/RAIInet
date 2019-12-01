#include "display.h"

using namespace std;

GDisplay::GDisplay(string l1, string l2, string a1, string a2){
	links = map<char, string>();
        pi = vector<PlayerInfo*>();
	pi.emplace_back(new PlayerInfo());
	pi.emplace_back(new PlayerInfo());
        turn = 0;
        for(size_t i = 0; i < l1.length() / 2; ++i){
                char p1Name = 'a' + i;
                char p2Name = 'A' + i;
                string p1Type = l1.substr(i * 2, 2);
                string p2Type = l2.substr(i * 2, 2);
                links[p1Name] = p1Type;
                links[p2Name] = p2Type;
                pi[0]->revealed.emplace_back(p1Name);
                pi[1]->revealed.emplace_back(p2Name);
        }
        for(size_t i = 0; i < a1.length(); ++i){
                pi[0]->abilities.emplace_back(a1[i]);
                pi[0]->abilityUsed.emplace_back(false);
                pi[1]->abilities.emplace_back(a2[i]);
                pi[1]->abilityUsed.emplace_back(false);
        }
	pi[0]->abilityUsed[2] = true;
	pi[0]->abilityUsed[0] = true;
	pi[1]->abilityUsed[4] = true;
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

GDisplay::~GDisplay() { for(auto p : pi) delete p; }

void GDisplay::notify(Subject<PInfo, PState> &whoNotified){
	const PState& state = whoNotified.getState();
        if(state.state == StateType::Download){
                if(whoNotified.getInfo().player == 0){
                        if(links[whoNotified.getInfo().link][0] == 'D') ++pi[0]->data;
                        else ++pi[0]->virus;
                } else {
                        if(links[whoNotified.getInfo().link][0] == 'V') ++pi[1]->data;
                        else ++pi[1]->virus;
                }
        } else if(state.state == StateType::Ability){
                if(turn == 0) pi[0]->abilityUsed[state.id] = true;
                else pi[1]->abilityUsed[state.id] = true;
        }
}

void GDisplay::notify(Subject<CInfo, CState> &whoNotified){
	int r = whoNotified.getInfo().row;
        int c = whoNotified.getInfo().col;
        board[r][c] = whoNotified.getInfo().link;
        if(whoNotified.getInfo().link == '.' && whoNotified.getInfo().isFirewall){
        	if(whoNotified.getInfo().playerFirewall) board[r][c] = 'w';
                else board[r][c] = 'm';
        }
	turn = !turn;
}

void GDisplay::notify(Subject<LInfo, LState> &whoNotified){
	for(auto p : pi) p->revealed.emplace_back(whoNotified.getInfo().link);
}

