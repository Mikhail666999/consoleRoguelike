#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
 
#include "src/entity.cpp"
#include "src/object.cpp"
 
const int MAP_X   = 90;
const int MAP_Y   = 39;
const int EMAX    = 30;
const int EVALUE  = 6;
const int OVALUE  = 6;
 
char map[MAP_Y][MAP_X];
Character entites[EMAX];
Object objects[EMAX];

int level = 0;

#include "src/goodfunc.cpp"

int main() {
    srand(time(NULL));
	init_map();
    start_ncurses();

    int i = 0;
    while(1) {
        int nx = entites[i].x;
        int ny = entites[i].y;

        if(!i) {
            draw_map(0);

            int key = getch();
            switch (key) {
                case 'k': ny--; break;
                case 'j': ny++; break;
                case 'h': nx--; break;
                case 'l': nx++; break;
                case 'q':
                    end_ncurses();
                    exit(0);
                    break;
            }

            if(map[ny][nx] == 'm') {
                int j = gete(nx, ny);

                entites[j].hp--;

                if(entites[j].hp <= 0) {
                    entites[j].kill();
                    map[ny][nx] = '.';
                }
            }
			if(map[ny][nx] == '!') {
				int j = geto(nx, ny);

				entites[0].hp += objects[j].hp;
				objects[j].kill();
			}

        }

        if(entites[i].i == 'm') {
            nx += sng(entites[0].x - nx);
            ny += sng(entites[0].y - ny);
            
            if (map[ny][nx] == entites[0].i) {
                entites[0].hp--;
                if (entites[0].hp <= 0) {
                    end_ncurses();
                    exit(0);
                }
            }
        }

        if(entites[i].i && map[ny][nx] == '.' || map[ny][nx] == '!') {
            map[entites[i].y][entites[i].x] = '.';
            entites[i].x = nx;
            entites[i].y = ny;
            map[ny][nx] = entites[i].i;
        }
		

        i++;
        if (i == EVALUE+1) i = 0;
    }
    
    end_ncurses();
    return 0;
}
