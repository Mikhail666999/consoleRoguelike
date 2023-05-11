#include "entity.h"

void Character::add(int _x, int _y, char _i, int _hp) {
	x     = _x;
	y     = _y;
	i     = _i;
	hp    = _hp;
	k     = false;
}

void Character::kill() {
	i     = 0;
	hp    = 0;
	k     = true;
}
