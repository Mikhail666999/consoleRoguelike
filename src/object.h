#pragma once

class Object {
public:
    char i;
    int x, y, hp;

	void add(int _x, int _y, char _i, int _hp); 
	void kill();
};
