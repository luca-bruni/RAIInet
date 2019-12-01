#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "display.h"
#include "window.h"

class GraphicsDisplay: public GDisplay {
	Xwindow *win;
	const int offset = 2;
	const int boardY = 150;
	const int boardSize = 500;
	const int cellSize = 62;
	const int pieceSize = 50;
	const int xTextOffset = 22;
	const int yTextOffset = 29;
	const int cardXSize = 70;
	const int cardYSize = 85;
	void drawCard(int x, int y, int id, char type, int player);
	void displayPlayer(int player) override;
	void drawPiece(int x, int y, char name);
	public:
		void swapTurn();
		GraphicsDisplay(std::string l1, std::string l2, 
				std::string a1, std::string a2);
		~GraphicsDisplay();
		void display() override;
		void displayAbilities() override;
		void printError(std::string msg) override;
};

#endif
