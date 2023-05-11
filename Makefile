CC=g++
FILE=main.cpp
LIB=-lncursesw

all: clear compile start

compile:
	$(CC) $(FILE) $(LIB) -g -o roguelike

start:
	./roguelike

clear:
	clear

gdb:
	gdb ./roguelike