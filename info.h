#ifndef INFO_H
#define INFO_H

struct Info {
	int player; // Which player is the action from
	int row; // The row of the cell
	int col; // The column of the cell
	bool isFirewall; // If there is a firewall on the cell
	int playerFirewall; // Which player has the firewall
	char link; // The name of the link
	bool isBoosted; // Whether the-link is boosted or not
};

#endif
