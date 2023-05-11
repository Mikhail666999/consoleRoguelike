void start_ncurses() {
    initscr();
    cbreak();
}

void end_ncurses() {
    endwin();
}

void draw_ui() {
	mvprintw(0, 0, "Level: %i", level);
	mvprintw(1, 0, "Hp: %i",    entites[0].hp);
}

int nrandom(int v1, int v2) {
    return v1 + rand() % (v2 - v1);
}

void draw_map(int num) {
    clear();
	draw_ui();
    int view = 5, ui = 10;
	for (int y = 0; y < MAP_Y - 1; y++) {
        for (int x = 0; x < MAP_X - 1; x++) {
        	if (num) {
	        	if (x < entites[0].x + view && y < entites[0].y + view &&
					x > entites[0].x - view && y > entites[0].y - view) {
					//mvaddch(y, x, ' ');
	            	mvaddch(y, x + ui, map[y][x]);
				}
	        	else {
					mvaddch(y, x + ui, ' ');
	        	}
	        } else {
	        	mvprintw(y, x + ui, "%c", map[y][x]);
	        }
        }
    }
}

void fill_map(char c) {
	for (int y = 0; y < MAP_Y; y++) {
        for (int x = 0; x < MAP_X; x++) {
            map[y][x] = c;
        }
    }
}

void region_create(int x1, int x2, int y1, int y2, char c) {
	for (int y = y1; y < y2; y++) {
    	for (int x = x1; x < x2; x++) {
            map[y][x] = c;
        }
    }
}

int gete(int x, int y) {
    for (int i = 1; i < EMAX; ++i) {
        if((entites[i].x == x) && (entites[i].y == y)) return i;
    }
    return -1;
}

int geto(int x, int y) {
	for (int i = 1; i < EMAX; ++i) {
        if((objects[i].x == x) && (objects[i].y == y)) return i;
    }
    return -1;
}

// add entity
void adde(int x, int y, char c, int hp) {
    for (int i = 0; i < EMAX; i++) {
        if (!entites[i].i) {
            entites[i].add(x, y, c, hp);
            return;
        }
    }
}

void entity_random_place(char c, int hp) {
    int x, y;
    do
    {
        x = nrandom(0, MAP_X - 1);
        y = nrandom(0, MAP_Y - 1);

        if (map[y][x] == '.') {
            map[y][x] = c;
            adde(x, y, c, hp);
            return;
        }
    } while (1);
}

// add object
void addo(int x, int y, char c, int hp) {
    for (int i = 0; i < EMAX; i++) {
        if (!objects[i].i) {
            objects[i].add(x, y, c, hp);
            return;
        }
    }
}

void object_random_place(char c, int hp) {
	int x, y;
	do {
		x = nrandom(0, MAP_X - 1);
		y = nrandom(0, MAP_Y - 1);

		if (map[y][x] == '.') {
			map[y][x] = c;
			addo(x, y, c, hp);
			return;
		}
	} while (1);
}

void one_room_dungeon(  /*1*/     float xmass1, // Х Точка для комнатки (разбиратся в коде)
                    float xmass2, float xmass3, // Ширина комнаты

                        /*1*/     float ymass1, // Y Точка для комнатки
                    float ymass2, float ymass3) {// Высота комнаты
    int x1, x2, y1, y2, mx1, mx2, mx3, my1, my2, my3;
    for (int i = 0; i < (MAP_X + MAP_Y) * 1.5; i++) {
        /*X1*/              /*1*/               mx1 = (int) MAP_X * xmass1;
        /*X2*/     mx2 = (int) MAP_X * xmass2;  mx3 = (int) MAP_X * xmass3;

        /*Y1*/              /*1*/               my1 = (int) MAP_Y * ymass1;
        /*Y2*/     my2 = (int) MAP_Y * ymass2;  my3 = (int) MAP_Y * ymass3;

        x1 = nrandom(1,          MAP_X - mx1);  
        x2 = nrandom(x1 + mx2,   x1    + mx3);
        y1 = nrandom(1,          MAP_Y - my1); 
        y2 = nrandom(y1 + my2,   y1    + my3);

        region_create(x1, x2, y1, y2, '.');
    }

}

void init_map() {
    region_create(0, MAP_X - 1, 0, MAP_Y - 1, '#');

    one_room_dungeon(/*1*/   0.2, 
                      0.1,   0.15,

                     /*1*/   0.2,
                      0.1,   0.15);
	level += 1;
    
    // add player
    entity_random_place('@', 5);

    // add entites
    for (int i = 1; i < EVALUE + 1; ++i) {
        entity_random_place('m', 2);
    }

	// add objects
	for (int i = 0; i < OVALUE + 1; i++) {
		object_random_place('!', 2);
	}
}

int sng(int x) {
    return (x > 0) - (x < 0);
}
