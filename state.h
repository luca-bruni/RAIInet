#ifndef STATE_H
#define STATE_H

enum class StateType {Move, Reveal, Delete};
enum class Direction {Up, Down, Left, Right};

struct State {
	StateType state;
	Direction dir;
};

#endif
