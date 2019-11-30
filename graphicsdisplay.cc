#include "graphicsdisplay.h"

#include <iostream> //TESTING ------------------------------------------------

using namespace std;

GraphicsDisplay::GraphicsDisplay(string l1, string l2, string a1, string a2):
				GDisplay{l1,l2,a1,a2}, win{new Xwindow(500, 800)}{}

GraphicsDisplay::~GraphicsDisplay() { delete win; }

void GraphicsDisplay::drawCard(int x, int y, int id, char type, int player){
	string cardName = "";
	int nameOffset = 0;
	if(type == 'L') {cardName = "Link Boost"; nameOffset = 2;}
	else if(type == 'F') {cardName = "Firewall"; nameOffset = 4;}
	else if(type == 'D') {cardName = "Download"; nameOffset = 4;}
	else if(type == 'S') {cardName = "Scan"; nameOffset = 8;}
	else if(type == 'P') {cardName = "Polarize"; nameOffset = 4;}
	if(turn == player) {
		if(pi[player]->abilityUsed[id]){
			win->fillRectangle(x, y, cardXSize, cardYSize, Xwindow::Red);
		} else {
			win->fillRectangle(x, y, cardXSize, cardYSize,
					Xwindow::Green);
		}
	}
	win->fillRectangle(x + offset, y + offset, cardXSize - offset * 2,
				cardYSize - offset * 2, Xwindow::Brown);
	win->drawString(x + offset + 6, y + offset + 6, to_string(id + 1));
	if(turn == player){
		win->drawString(x + nameOffset, y + pieceSize, cardName);
	}
}

void GraphicsDisplay::displayPlayer(int player){
	int iy = (boardY + boardSize) * player;
	win->drawString(10, iy + 10, "Player " + to_string(player + 1) + ": ");
	for(int i = 0; i < pi[player]->data; ++i){
		drawPiece(10 + i * cellSize / 2, iy + 25, 'T');
	}
	for(int i = 0; i < pi[player]->virus; ++i){
		drawPiece(10 + (i + 4) * cellSize / 2, iy + 25, 'V');
	}
	for(int i = 0; i < pi[player]->abilities.size(); ++i){
		drawCard(10 + i * (cardXSize + 4), iy + 60, i, 
				pi[player]->abilities[i], player);
	}
}

void GraphicsDisplay::drawPiece(int x, int y, char name){
	if(name == 'S') {
		win->fillRectangle(x, y, pieceSize, pieceSize, Xwindow::Gray);
		win->fillRectangle(x + offset, y + offset, pieceSize - 2 * offset,
					pieceSize - 2 * offset, Xwindow::Gold);
	} else if(name >= 'a' && name <= 'h'){
		win->fillRectangle(x, y, pieceSize, pieceSize, Xwindow::Gray);
		win->fillRectangle(x + offset, y + offset, pieceSize - 2 * offset,
					pieceSize - 2 * offset, Xwindow::Tan);
		win->drawString(x + xTextOffset, y + yTextOffset, string(1, name));
	} else if(name >= 'A' && name <= 'H'){
		win->fillRectangle(x, y, pieceSize, pieceSize, Xwindow::Gray);
		win->fillRectangle(x + offset, y + offset, pieceSize - 2 * offset,
					pieceSize - 2 * offset, Xwindow::Brown);
		win->drawString(x + xTextOffset, y + yTextOffset, string(1, name));
	} else if(name == 'T'){
		win->fillRectangle(x + offset, y + offset, pieceSize / 2 - 2 * offset,
					pieceSize / 2 - 2 * offset, Xwindow::Green);
	} else if(name == 'V'){
		win->fillRectangle(x + offset, y + offset, pieceSize / 2 - 2 * offset,
					pieceSize / 2 - 2 * offset, Xwindow::Red);
	}
}

void GraphicsDisplay::display(){
	displayPlayer(0);
	int iY = boardY + offset;
	int iX = offset;
	win->fillRectangle(0, boardY, boardSize, boardSize, Xwindow::Gray);
	for(size_t r = 0; r < board.size(); ++r){
		for(size_t c = 0; c < board[r].size(); ++c){
			if((r + c) % 2) {
				win->fillRectangle(iX + c * cellSize, iY + r * cellSize,
						cellSize, cellSize, Xwindow::Black);
			} else {
				win->fillRectangle(iX + c * cellSize, iY + r * cellSize,
						cellSize, cellSize, Xwindow::White);
			}
			drawPiece(iX + c * cellSize + (cellSize - pieceSize) / 2,
				  iY + r * cellSize + (cellSize - pieceSize) / 2,
				  board[r][c]);
		}
	}
	displayPlayer(1);
}

void GraphicsDisplay::displayAbilities() {}
