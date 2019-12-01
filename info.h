#ifndef INFO_H
#define INFO_H

struct PInfo {
	int player;
	char link;
};

struct CInfo {
	int row;
	int col;
	char link;
	bool isFirewall;
	int playerFirewall;
};

struct LInfo {
	int player;
	char link;
	bool isBoosted;
};

#endif
