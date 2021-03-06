#include "board.h"

using namespace std;

Board::Board() {}

void Board::init(string l1, string l2, string a1, string a2, vector<shared_ptr<GDisplay>> &displays){
	players = vector<unique_ptr<Player>>(); // Array of Player (auto-deallocs)
	players.emplace_back(make_unique<Player>(a1, 0)); // Player 1's Ability list
	players.emplace_back(make_unique<Player>(a2, 1)); // Player 2's Ability list
	board = vector<vector<Cell>>(); // Array of Cell
	for(int r = 0; r < boardSize; ++r){ // Looping through the Board's rows
		vector<Cell> row = vector<Cell>(); // Constructs a Cell at each row-start
		for(int c = 0; c < boardSize; ++c){ // Looping through the Board's cols
			row.emplace_back(Cell{r, c}); // Adds Cells to each row until end of cols
		}
		board.emplace_back(row); // Places entire row on board after all cols of row filled
	}
	for(int i = 0; i < boardSize; ++i){ // Loops through entire Board
		char p1 = 'a' + i; // Initialize p1 to 'a' through 'h' each iteration (P1)
		char p2 = 'A' + i; // Initiaize p2 to 'A' through 'H' each iteration (P2)
		shared_ptr<Link> link1(new Link(p1, l1[i * 2], l1[i * 2 + 1] - '0', 0)); // Link for each p1
		shared_ptr<Link> link2(new Link(p2, l2[i * 2], l2[i * 2 + 1] - '0', 1)); // Link for each p2
		links[p1] = link1; // Adds to Link array
		links[p2] = link2; // Adds to Link array
		if(i < 4) { // Server ports
			shared_ptr<Link> s = make_shared<Link>('S', 'S', 0, i / 2);
                	links['W' + i] = s;
		}
	}
	for(auto d : displays) setDisplay(d.get()); // Loops through displays for existence; sets as observer
	for(int i = 0; i < boardSize; ++i){ // Loops through Board and adds server ports accordingly at game start
		char p1 = 'a' + i;
		char p2 = 'A' + i;
		if(i == boardSize / 2 - 1 || i == boardSize / 2){
			board[0][i].setLink(links['W' + i - (boardSize / 2 - 1)]);
			board[7][i].setLink(links['Y' + i - (boardSize / 2 - 1)]);
                        board[1][i].setLink(links[p1]);
                        board[6][i].setLink(links[p2]);
                } else {
                        board[0][i].setLink(links[p1]);
                        board[7][i].setLink(links[p2]);
         	}
	}
	turn = 0;
}

void Board::setDisplay(GDisplay *d) {
	for(size_t i = 0; i < players.size(); ++i) players[i]->attach(d); // Attaches Players to display observer
	for(auto it : links) it.second->attach(d); // Attaches value (link) to display observer
	for(size_t r = 0; r < board.size(); ++r){ // Rows of Board
		for(size_t c = 0; c < board.size(); ++c) { // Cols of Board
			board[r][c].attach(d); // Attaches to display observer
		}
	}
}

bool Board::hasWon(){
	for(size_t i = 0; i < players.size(); ++i){ // Loops through each Player
		if(players[i]->getData() >= 4) return true; // Player has won if downloaded 4 data
		if(players[i]->getVirus() >= 4) return true; // Player has won if other downloaded 4 viruses
	}
	return false; // No Player has won if neither conditional holds
}

int Board::whoWon(){
	for(size_t i = 0; i < players.size(); ++i){ // Loops through each Player
		if(players[i]->getData() >= 4) return i; // Returns ID of Player that downloaded 4 data
		if(players[i]->getVirus() >= 4) return !i; // Returns ID of Player who didn't download 4 viruses
	}
	return -1; // Garbage value since requires hasWon()
}

void Board::move(char link, string dir){
	try {
		if(links.at(link)->getInfo().player != turn) throw "Not your piece."; // If in-permissable move on turn
	} catch (out_of_range e){
		throw "Not a valid link.";
	}
	int row = -1;
	int col = -1;
	for(size_t r = 0; r < board.size(); ++r){ // Loops through rows
		for(size_t c = 0; c < board[r].size(); ++c){ // Loops throw cols
			if(!board[r][c].getLink()) continue; // Re-iterates
			if (board[r][c].getLink()->getInfo().link == link) { // If Link found
				row = r; // Sets row to current row
				col = c; // Sets col to current column
			}
		}
	}
	Cell &origin = board.at(row).at(col); // Original position of piece via Cell
	int speed = 1 + links[link]->getInfo().isBoosted;
	if(dir == "up") row -= speed; // Move up
	else if(dir == "down") row += speed; // Move down
	else if(dir == "left") col -= speed; // Move left
	else if(dir == "right") col += speed; // Move right
	else throw "Not a valid direction to move in.";
	try {
		Cell &dest = board.at(row).at(col);
		if(dest.getInfo().isFirewall && dest.getInfo().playerFirewall != turn){
			links[link]->reveal();
			dest.setLink(origin.getLink());
			origin.setLink(nullptr);
			if(links[link]->getType() == 'V') {
				players[turn]->download(links[link]);
				dest.setLink(nullptr);
			}
		} else if(dest.getLink() != nullptr){ // If dest non-empty
			if(dest.getLink()->getInfo().player == turn){ // If piece on space owned by mover
				throw "Cannot move on your own piece.";
			} else if(dest.getLink()->getType() == 'S'){ // If dest is a server port
				players[!turn]->download(origin.getLink()); // Download on that port
				origin.setLink(nullptr); // Since move successful, origin is nullptr now
			} else { // Must be on enemy player
				battle(origin, dest); // Commence a battle
			}
		} else { // If dest is empty
			dest.setLink(origin.getLink()); // Sets dest's link to that of origin
			origin.setLink(nullptr); // Sets the link of origin to nullptr
		}
		turn = !turn; // Flips turn since move was successful
		abilityUsed = false;
	} catch (out_of_range e) {
                if(dir == "down" && turn == 0){ // If out_of_range at bottom and Player 1's turn
                        players[0]->download(origin.getLink()); // Player 1 downloads that Link
                        origin.setLink(nullptr); // Set that link to nullptr
			turn = !turn; // Flips turn
			abilityUsed = false;
                } else if(dir == "up" && turn == 1){ // If out_of_range at top and Player 2's turn
                        players[1]->download(origin.getLink()); // Player 2 downloads that Link
                        origin.setLink(nullptr); // Sets that link to nullptr
			turn = !turn; // Flips turn
			abilityUsed = false;
                } else {
                        throw "Invalid move."; // No out_of_range is happening; genuine out of boundaries
                }
        }

}

void Board::battle(Cell &origin, Cell &dest){
	// True if origin's Link is enraged; false otherwise
	bool oEnraged = origin.getLink()->getInfo().isEnraged;
	// True if dest's Link is enraged; false otherwise
	bool dEnraged = dest.getLink()->getInfo().isEnraged;
	origin.getLink()->reveal(); // Reveal origin link to all
	dest.getLink()->reveal(); // Reveal dest link to all
	
	if ((oEnraged && dEnraged) || !(oEnraged || dEnraged)) { // If both or neither Links are enraged
		// If mover's link-strength greater-equal than other link:
		if(origin.getLink()->getStrength() >= dest.getLink()->getStrength()){
			players[turn]->download(dest.getLink()); // Mover downloads the lesser Link
			dest.setLink(origin.getLink()); // Stronger Link remains at dest's location
		} else { // If mover's link-strength is less than other link:
			players[!turn]->download(origin.getLink()); // Other player downloads the Link
		}
	}
	else { // If one Link is enraged
		if (oEnraged) { // If origin Link is enraged
			players[turn]->download(dest.getLink());
			dest.setLink(origin.getLink());
			origin.getLink()->setEnraged(false); // Enrage ability expires
		} else { // If dest Link is enraged
			players[!turn]->download(origin.getLink()); // Other player downloads the Link
			dest.getLink()->setEnraged(false); // Enrage ability expires
		}
	}
	origin.setLink(nullptr); // One Link remains
}

void Board::useAbility(int id, char link){
	try {
		if(abilityUsed) throw "Already used ability this turn.";
		if(links.at(link)->getType() == 'S') throw out_of_range("Not a valid link.");
		players[turn]->useAbility(id, links.at(link).get()); // Calls useAbility on a Link
		abilityUsed = true;
	} catch (out_of_range e){
		throw "That is not a valid link.";
	}
}

void Board::useAbility(int id, int row, int col){
	try {
		if(abilityUsed) throw "Already used ability this turn.";
		players[turn]->useAbility(id, &board.at(row - 1).at(col - 1)); // Calls useAbility on a Cell
		abilityUsed = true;
		
	} catch (out_of_range e){
		throw "That is not a valid cell.";
	}
}

void Board::useAbility(int id) {
	if(abilityUsed) throw "Already used ability this turn.";
	players[turn]->useAbility(id); // Calls useAbility on self
}
