#include "display.h"
#include <iostream>

using namespace std;

GDisplay::GDisplay(string l1, string l2, string a1, string a2){
	links = map<char, string>();
	firewalls = map<pair<int, int>, int>();
        pi = vector<unique_ptr<PlayerInfo>>();
	pi.emplace_back(make_unique<PlayerInfo>());
	pi.emplace_back(make_unique<PlayerInfo>());
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
        board = vector<vector<char>>();
        for(int r = 0; r < boardSize; ++r){
                vector<char> row = vector<char>();
                for(int c = 0; c < boardSize; ++c){
                        row.emplace_back('.');
                }
                board.emplace_back(row);
        }
}

GDisplay::~GDisplay() {}

void GDisplay::notify(Subject<PInfo, PState> &whoNotified){
	const PState& state = whoNotified.getState();
        if(state.state == StateType::Download){
                if(whoNotified.getInfo().player == 0){
                        if(links[whoNotified.getState().linkType][0] == 'D') ++pi[0]->data;
                        else ++pi[0]->virus;
                } else {
                        if(links[whoNotified.getState().linkType][0] == 'V') ++pi[1]->data;
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
	char oldBoard = board[r][c];
	if(whoNotified.getState().state == StateType::Firewall){
        	firewalls[std::make_pair(r, c)] = whoNotified.getInfo().playerFirewall;
		display();
        }
	if(whoNotified.getState().state == StateType::CellChange) {
		board[r][c] = whoNotified.getState().link;
		if(oldBoard != '.' && board[r][c] == '.'){
			turn = !turn;
		}
	}
}

void GDisplay::notify(Subject<LInfo, LState> &whoNotified){
	for(int i = 0; i < pi.size(); ++i) pi[i]->revealed.emplace_back(whoNotified.getInfo().link);
}

