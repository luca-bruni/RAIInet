#ifndef STATE_H
#define STATE_H

enum class StateType {Download, Ability, CellChange, Reveal};

struct State {
	StateType state; // The State of the Player
	int id; // The ability ID the Player is using
	char link; // The link the cell is changing to
};

#endif
