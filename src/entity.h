#pragma once

#include <stdio.h>
#include <stdlib.h>

class Character {
public:
	char i;
	int x, y, hp;
	bool k;

	void add(int _x, int _y, char i, int hp);
	void kill();
};
