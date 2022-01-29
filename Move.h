

void Normal_Move(char* st) {
	for(int i = 1; i <= CELL_WIDTH; i++) 
		for(int j = 1; j <= CELL_HEIGHT; j++) 
			Is_In_Move[i][j] = false;
	Is_In_Move[rt->x][rt->y] = true;
	for(int k = 1; k <= 3; k++) {
		for(int i = 1; i <= CELL_WIDTH; i++) {
			for(int j = 1; j <= CELL_HEIGHT; j++) {
				if(strcmp(st, WHO_IS_JACK) == 0 && Is_In_Move[i][j] == true && k == 3 && Jack_Show == false) {
					if(gcell[i][j].exit == true) {
						for(int h = 0; h < EXIT_NUMBER; h++) {
							if(i == gexit[h].x && j == gexit[h].y && gexit[h].sit == true) {
								JACK_WIN();
								BUTTON_END = true;
								return;
							}
						}
					}
				}
				if(Is_In_Move[i][j] || gcell[i][j].house || gcell[i][j].light)
					continue;
				if(i % 2 == 0) {
					if(Is_In_Move[i - 1][j] || Is_In_Move[i - 1][j - 1] || Is_In_Move[i][j + 1] || Is_In_Move[i][j - 1] || Is_In_Move[i + 1][j] || Is_In_Move[i + 1][j - 1]) {
						struct Move_Plans* nw = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
						nw->x = i;
						nw->y = j; 
						nw->nxt = rt->nxt;
						rt->nxt = nw;
						if(IS_CHARECTER_IN(i, j)) 
							nw->JACK_Capture = true;
						else 
							nw->JACK_Capture = false;
					}
				}
				if(i % 2 == 1) {
					if(Is_In_Move[i - 1][j] || Is_In_Move[i - 1][j + 1] || Is_In_Move[i][j + 1] || Is_In_Move[i][j - 1] || Is_In_Move[i + 1][j] || Is_In_Move[i + 1][j + 1]) {
						struct Move_Plans* nw = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
						nw->x = i;
						nw->y = j;
						nw->nxt = rt->nxt;
						rt->nxt = nw;
						if(IS_CHARECTER_IN(i, j)) 
							nw->JACK_Capture = true;
						else 
							nw->JACK_Capture = false;
					}
				}
			}
		}
		for(int i = 0; i < HOLES_NUMBER; i++) {
			if(Is_In_Move[ghole[i].x][ghole[i].y] == true && ghole[i].sit == true) {
				for(int j = 0; j < HOLES_NUMBER; j++) {
					if(i != j && ghole[j].sit && Is_In_Move[ghole[j].x][ghole[j].y] == false) {
						struct Move_Plans* nw = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
						nw->x = ghole[j].x;
						nw->y = ghole[j].y;
						nw->nxt = rt->nxt;
						rt->nxt = nw;
					}
				}
			}
		}
		struct Move_Plans* nd = rt->nxt;
		while(nd != NULL) {
			Is_In_Move[nd->x][nd->y] = true;
			nd = nd->nxt;
		}
	}
}

void MS_MOVE() {
	for(int i = 1; i <= CELL_WIDTH; i++) 
		for(int j = 1; j <= CELL_HEIGHT; j++) 
			Is_In_Move[i][j] = false;
	Is_In_Move[rt->x][rt->y] = true;
	for(int k = 1; k <= 3; k++) {
		for(int i = 1; i <= CELL_WIDTH; i++) {
			for(int j = 1; j <= CELL_HEIGHT; j++) {
				if(strcmp("MS", WHO_IS_JACK) == 0 && Is_In_Move[i][j] == true && k == 3 && Jack_Show == false) {
					if(gcell[i][j].exit == true) {
						for(int h = 0; h < EXIT_NUMBER; h++) {
							if(i == gexit[h].x && j == gexit[h].y && gexit[h].sit == true) {
								JACK_WIN();
								BUTTON_END = true;
								return;
							}
						}
					}
				}
				if(Is_In_Move[i][j])
					continue;
				if(i % 2 == 0) {
					if(Is_In_Move[i - 1][j] || Is_In_Move[i - 1][j - 1] || Is_In_Move[i][j + 1] || Is_In_Move[i][j - 1] || Is_In_Move[i + 1][j] || Is_In_Move[i + 1][j - 1]) {
						struct Move_Plans* nw = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
						nw->x = i;
						nw->y = j;
						nw->nxt = rt->nxt;
						rt->nxt = nw;
						if(IS_CHARECTER_IN(i, j)) 
							nw->JACK_Capture = true;
						else 
							nw->JACK_Capture = false;
					}
				}
				if(i % 2 == 1) {
					if(Is_In_Move[i - 1][j] || Is_In_Move[i - 1][j + 1] || Is_In_Move[i][j + 1] || Is_In_Move[i][j - 1] || Is_In_Move[i + 1][j] || Is_In_Move[i + 1][j + 1]) {
						struct Move_Plans* nw = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
						nw->x = i;
						nw->y = j;
						nw->nxt = rt->nxt;
						rt->nxt = nw;
						if(IS_CHARECTER_IN(i, j)) 
							nw->JACK_Capture = true;
						else 
							nw->JACK_Capture = false;
					}
				}
			}
		}
		for(int i = 0; i < HOLES_NUMBER; i++) {
			if(Is_In_Move[ghole[i].x][ghole[i].y] == true && ghole[i].sit == true) {
				for(int j = 0; j < HOLES_NUMBER; j++) {
					if(i != j && ghole[j].sit && Is_In_Move[ghole[j].x][ghole[j].y] == false) {
						struct Move_Plans* nw = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
						nw->x = ghole[j].x;
						nw->y = ghole[j].y;
						nw->nxt = rt->nxt;
						rt->nxt = nw;
					}
				}
			}
		}
		struct Move_Plans* nd = rt->nxt;
		while(nd != NULL) {
			Is_In_Move[nd->x][nd->y] = true;
			nd = nd->nxt;
		}
	}
	struct Move_Plans* nd = rt->nxt;
	struct Move_Plans* pre = rt;
	while(nd != NULL) {
		if(gcell[nd->x][nd->y].light || gcell[nd->x][nd->y].house) {
			pre->nxt = nd->nxt;
			nd = nd->nxt;
		}
		else {
			pre = nd;
			nd = nd->nxt;
		}
	}
}