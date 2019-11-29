#include "observer.h"
#include "subject.h"
#include "playerinfo.h"
#include "state.h"
#include "info.h"
#include <vector>
#include <map>

class Display: public Observer<Info, State> {
	const int boardSize = 8;
	const int handSize = 5;
	protected:
		std::vector<std::vector<char>> board;
		std::map<char, std::string> links;
		std::vector<PlayerInfo*> pi;
		int turn;
		virtual void displayPlayer(int player) = 0;
	public:
		Display(std::string l1, std::string l2, std::string a1, std::string a2);
		~Display();
		void notify(Subject<Info, State> &whoNotified);
		virtual void display() = 0;
		virtual void displayAbilities() = 0;
};
