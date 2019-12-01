#include "board.h"

using namespace std;

Board::Board() {}

void Board::init(string l1, string l2, string a1, string a2){
	players = vector<unique_ptr<Player>>();
	players.emplace_back(make_unique<Player>(a1));
	players.emplace_back(make_unique<Player>(a2));
	board = vector<vector<Cell>>();
	for(int r = 0; r < boardSize; ++r){
		vector<Cell> row = vector<Cell>();
		for(int c = 0; c < boardSize; ++c){
			row.emplace_back(Cell{r, c});
		}
		board.emplace_back(row);
	}
	for(int i = 0; i < boardSize; ++i){
		char p1 = 'a' + i;
		char p2 = 'A' + i;
		shared_ptr<Link> link1(new Link(p1, l1[i * 2], l1[i * 2 + 1] - '0', 0));
		shared_ptr<Link> link2(new Link(p2, l2[i * 2], l2[i * 2 + 1] - '0', 1));
		links[p1] = link1;
		links[p2] = link2;
		
		if(i == boardSize / 2 - 1 || i == boardSize / 2){
			board[1][i].setLink(link1);
			board[6][i].setLink(link2);
		} else {
			board[0][i].setLink(link1);
			board[7][i].setLink(link2);
		}
	}
	
	for(int i = 0; i < 4; ++i){
		shared_ptr<Link> s = make_shared<Link>('S', 'S', 0, i / 2);
		links['W' + i] = s;
		board[(boardSize / 2 - 1) + i % 2][(boardSize - 1) * i].setLink(s);
	}
}

void Board::setDisplay(GDisplay *d){
	for(int i = 0; i < players.size(); ++i) players[i]->attach(d);
	for(auto it : links) it.second->attach(d);
	for(auto row : board)
		for(auto cell : row) cell.attach(d);
}

bool Board::hasWon(){
	for(int i = 0; i < players.size(); ++i){
		if(players[i]->getData() >= 4) return true;
		if(players[i]->getVirus() >= 4) return true;
	}
	return false;
}

int Board::whoWon(){
	for(int i = 0; i < players.size(); ++i){
		if(players[i]->getData() >= 4) return i;
		if(players[i]->getVirus() >= 4) return !i;
	}
	return -1;
}

void Board::move(char link, string dir){
	int row = -1;
	int col = -1;
	for(int r = 0; r < board.size(); ++r)
		for(int c = 0; c < board[r].size(); ++c)
			if(board[r][c].getLink()->getInfo().link == link) {
				row = r;
				col = c;
			}
	Cell &origin = board[row][col];
	if(dir == "up") row -= 1;
	else if(dir == "down") row += 1;
	else if(dir == "left") col -= 1;
	else col += 1;
	try {
		Cell &dest = board[row][col];
		if(dest.getLink() != nullptr){
			if(dest.getLink()->getInfo().player == turn){
				throw "Incorrect move.";
			} else if(dest.getLink()->getType() == 'S'){
				players[!turn]->download(origin.getLink());
				origin.setLink(nullptr);
			} else {
				battle(origin, dest);
			}
		} else {
			dest.setLink(origin.getLink());
			origin.setLink(nullptr);
		}
		turn = !turn;
	} catch (out_of_range e) {
                if(dir == "down" && turn == 0){
                        players[0]->download(origin.getLink());
                        origin.setLink(nullptr);
                } else if(dir == "up" && turn == 1){
                        players[1]->download(origin.getLink());
                        origin.setLink(nullptr);
                } else {
                        throw e;
                }
        }

}

void Board::battle(Cell &origin, Cell &dest){
	origin.getLink()->reveal();
	dest.getLink()->reveal();
	if(origin.getLink()->getStrength() >= dest.getLink()->getStrength()){
		players[turn]->download(dest.getLink());
		dest.setLink(origin.getLink());
	} else {
		players[!turn]->download(origin.getLink());
	}
	origin.setLink(nullptr);
}

void Board::useAbility(int id, char link){
	players[turn]->useAbility(id, links[link].get());
}

void Board::useAbility(int id, int row, int col){
	players[turn]->useAbility(id, &board.at(row).at(col));
}
