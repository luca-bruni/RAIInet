#ifndef STATE_H
#define STATE_H

enum class StateType {Move, Reveal, Delete, Download, Ability};
enum class Direction {Up, Down, Left, Right};

struct State {
	StateType state; // The State of the Player or Link
	Direction dir; // The direction the Link is moving
	int id; // The ability ID the Player is using
	int player; // Which player this action is directed at
};

#endif
