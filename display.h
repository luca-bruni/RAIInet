#ifndef DISPLAY_H
#define DISPLAY_H

#include "observer.h"
#include "subject.h"
#include "playerinfo.h"
#include "state.h"
#include "info.h"
#include <vector>
#include <map>
#include <memory>

class GDisplay: public Observer<PInfo, PState>, public Observer<CInfo, CState>, 
						public Observer<LInfo, LState>{
	const int boardSize = 8;
	const int handSize = 5;
	protected:
		std::vector<std::vector<char>> board;
		std::map<char, std::string> links;
		std::map<std::pair<int, int>, int> firewalls;
		std::vector<std::unique_ptr<PlayerInfo>> pi;
		int turn;
		virtual void displayPlayer(int player) = 0;
	public:
		GDisplay(std::string l1, std::string l2, std::string a1, std::string a2);
		~GDisplay();
		void notify(Subject<PInfo, PState> &whoNotified);
		void notify(Subject<CInfo, CState> &whoNotified);
		void notify(Subject<LInfo, LState> &whoNotified);
		virtual void display() = 0;
		virtual void displayAbilities() = 0;
		virtual void printMsg(std::string msg) = 0;
};

#endif
