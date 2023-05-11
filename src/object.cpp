#include "object.h"

void Object::add(int _x, int _y, char _i, int _hp) {
	x  = _x;
	y  = _y;
	i  = _i;
	hp = _hp;
}

void Object::kill() {
	i = 0;
}
