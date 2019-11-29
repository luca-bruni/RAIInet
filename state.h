#ifndef STATE_H
#define STATE_H

enum class StateType {CellChange, Reveal, Download, Ability};

struct State {
	StateType state; // The State of the Player or Link
	int id; // The ability ID the Player is using
	int player; // Which player this action is directed at
};

#endif
