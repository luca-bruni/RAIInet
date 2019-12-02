#ifndef STATE_H
#define STATE_H

enum class StateType {Download, Ability, CellChange, Reveal, Firewall};

struct PState {
	StateType state;
	int id;
	char linkType;
};

struct CState {
	StateType state;
	char link;
};

struct LState {
	StateType state;
	char link;
};

#endif
