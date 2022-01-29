
bool JSAbility(SDL_Event* e) {
	if(JS_SITUATION.x == 0 && JS_SITUATION.y == 0) {
		for(int k = 0; k < LIGHT_NUMBER; k++) {
			if(glight[k].sit == true)
				continue;
			int i = glight[k].x, j = glight[k].y;
			if(Inside_CELL(e, i, j) == BUTTON_SPRITE_MOUSE_DOWN) {
				JS_SITUATION.x = i, JS_SITUATION.y = j;
				JS_SITUATION.id = k;
				return false;
			}					
		}
	}
	else {
		for(int k = 0; k < LIGHT_NUMBER; k++) {
			if(glight[k].sit == false)
				continue;
			int i = glight[k].x, j = glight[k].y;
			if(Inside_CELL(e, i, j) == BUTTON_SPRITE_MOUSE_DOWN) {
				glight[k].sit = false;
				glight[JS_SITUATION.id].sit = true;
				JS_SITUATION.x = JS_SITUATION.y = JS_SITUATION.id = 0;
				return true;
			}					
		}
	}
	return false;
}

bool ILAbility(SDL_Event* e) {
	if(IL_SITUATION.x == 0 && IL_SITUATION.y == 0) {
		for(int k = 0; k < EXIT_NUMBER; k++) {
			if(gexit[k].sit == true)
				continue;
			int i = gexit[k].x, j = gexit[k].y;
			if(Inside_CELL(e, i, j) == BUTTON_SPRITE_MOUSE_DOWN) {
				IL_SITUATION.x = i, IL_SITUATION.y = j;
				IL_SITUATION.id = k;
				return false;
			}					
		}
	}
	else {
		for(int k = 0; k < EXIT_NUMBER; k++) {
			if(gexit[k].sit == false)
				continue;
			int i = gexit[k].x, j = gexit[k].y;
			if(Inside_CELL(e, i, j) == BUTTON_SPRITE_MOUSE_DOWN) {
				gexit[k].sit = false;
				gexit[IL_SITUATION.id].sit = true;
				IL_SITUATION.x = IL_SITUATION.y = IL_SITUATION.id = 0;
				return true;
			}		
		}
	}
	return false;
}

bool JBAbility(SDL_Event* e) {
	if(JB_SITUATION.x == 0 && JB_SITUATION.y == 0) {
		for(int k = 0; k < HOLES_NUMBER; k++) {
			if(ghole[k].sit == true)
				continue;
			int i = ghole[k].x, j = ghole[k].y;
			if(Inside_CELL(e, i, j) == BUTTON_SPRITE_MOUSE_DOWN) {
				JB_SITUATION.x = i, JB_SITUATION.y = j;
				JB_SITUATION.id = k;
				return false;
			}					
		}
	}
	else {
		for(int k = 0; k < HOLES_NUMBER; k++) {
			if(ghole[k].sit == false)
				continue;
			int i = ghole[k].x, j = ghole[k].y;
			if(Inside_CELL(e, i, j) == BUTTON_SPRITE_MOUSE_DOWN) {
				ghole[k].sit = false;
				ghole[JB_SITUATION.id].sit = true;
				JB_SITUATION.x = JB_SITUATION.y = JB_SITUATION.id = 0;
				return true;
			}		
		}
	}
	return false;
}

void SHAbility() {
	int sz = 0;
	struct Linked_List* nd = SHcharecter->nxt;
	struct Linked_List* nh;
	while(nd != NULL) {
		sz++;
		nh = gcharecter->nxt;	
		while(nh != NULL) {
			
			if(strcmp(nh->str, nd->str) == 0) {
				nd->x = nh->x;
				nd->y = nh->y;
				break;
			}
			nh = nh->nxt;
		}		
		nd = nd->nxt;
	}
	int cnt = rand() % sz;
	nd = SHcharecter->nxt;
	struct Linked_List* pre = SHcharecter;
	while(cnt && nd != NULL) {
		pre = nd;
		nd = nd->nxt;
		cnt--;
	}
	pre->nxt = nd->nxt;
	nh = gcharecter->nxt;
	while(nh != NULL) {
		if(nh->x == nd->x && nh->y == nd->y) {
			nh->Innocent = true;
			break;
		}
		nh = nh->nxt;
	}
	cnt = 100;
	while(cnt--) {
  		SDL_SetRenderDrawColor(gRenderer, 102, 94, 76, 0);
  		SDL_RenderClear(gRenderer);
  		SDL_Event sdlEvent;
  		int SHUTDOWNCODE=0;
	    while (SDL_PollEvent(&sdlEvent)) {
	        if (sdlEvent.type==SDL_QUIT) {
	            SHUTDOWNCODE=1;
	            break;
	        }
	    }
	    if (SHUTDOWNCODE) break;
		char t[21] = "JACK IS NOT --->>>>>";
		SDL_Color color = {0, 0, 0};
		Print(t, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, color);	
		Print(nd->str, SCREEN_WIDTH / 4 + 250, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, color);	
		SDL_RenderPresent(gRenderer);
  		SDL_Delay(1000/FPS);
  	}
}

bool WGAbility(SDL_Event* e) {
	struct Linked_List* nd = gcharecter->nxt;
	struct Linked_List* nw = gcharecter;
	struct Linked_List* nh = NULL;
	while(nd != NULL) {
		if(strcmp(nd->str, "WG") == 0) 
			nw = nd;
		else if(Inside_CELL(e, nd->x, nd->y) == BUTTON_SPRITE_MOUSE_DOWN) {
			nh = nd;
			break;
		}
		nd = nd->nxt;
	}
	if(nh == NULL)
		return false;
	int x1 = nw->x, x2 = nh->x, y1 = nw->y, y2 = nh->y;
	Change_Location(x1, y1, 0, 0);
	Change_Location(x2, y2, x1, y1);
	Change_Location(0, 0, x2, y2);
	return true;
}

bool JWAbility(SDL_Event* e) {
	struct Linked_List* nd = gcharecter->nxt;
	struct Linked_List* nw = gcharecter;
	while(nd != NULL) {
		if(strcmp(nd->str, "JW") == 0) 
			nw = nd;
		nd = nd->nxt;
	}
	nd = nw;
	if(nd->y > 1 && Inside_CELL(e, nd->x, nd->y - 1) == BUTTON_SPRITE_MOUSE_DOWN) {
		JW_LIGHT = UP;
		return true;
	}
	else if(nd->y < CELL_HEIGHT && Inside_CELL(e, nd->x, nd->y + 1) == BUTTON_SPRITE_MOUSE_DOWN) {
		JW_LIGHT = DOWN;
		return true;
	}
	else {
		if(nd->x % 2 == 0) {
			if(nd->x > 1 && nd->y > 1 && Inside_CELL(e, nd->x - 1, nd->y - 1) == BUTTON_SPRITE_MOUSE_DOWN) {
				JW_LIGHT = LEFT_UP;
				return true;
			}
			else if(nd->x > 1 && Inside_CELL(e, nd->x - 1, nd->y) == BUTTON_SPRITE_MOUSE_DOWN) {
				JW_LIGHT = LEFT_DOWN;
				return true;
			}
			else if(nd->x < CELL_WIDTH && nd->y > 1 && Inside_CELL(e, nd->x + 1, nd->y - 1) == BUTTON_SPRITE_MOUSE_DOWN) {
				JW_LIGHT = RIGHT_UP;
				return true;
			}
			else if(nd->x < CELL_WIDTH && Inside_CELL(e, nd->x + 1, nd->y) == BUTTON_SPRITE_MOUSE_DOWN) {
				JW_LIGHT = RIGHT_DOWN;
				return true;
			}
		}
		else {
			if(nd->x > 1 && Inside_CELL(e, nd->x - 1, nd->y) == BUTTON_SPRITE_MOUSE_DOWN) {
				JW_LIGHT = LEFT_UP;
				return true;
			}
			else if(nd->x > 1 && nd->y < CELL_HEIGHT && Inside_CELL(e, nd->x - 1, nd->y + 1) == BUTTON_SPRITE_MOUSE_DOWN) {
				JW_LIGHT = LEFT_DOWN;
				return true;
			}
			else if(nd->x < CELL_WIDTH && Inside_CELL(e, nd->x + 1, nd->y) == BUTTON_SPRITE_MOUSE_DOWN) {
				JW_LIGHT = RIGHT_UP;
				return true;
			}
			else if(nd->x < CELL_WIDTH && nd->y < CELL_HEIGHT && Inside_CELL(e, nd->x + 1, nd->y + 1) == BUTTON_SPRITE_MOUSE_DOWN) {
				JW_LIGHT = RIGHT_DOWN;
				return true;
			}
		}
	}
	return false;
}

bool SGAbility(SDL_Event* e) {
	struct Linked_List* nd = gcharecter->nxt;
	struct Linked_List* nw = gcharecter;
	while(nd != NULL) {
		if(strcmp(nd->str, "SG") == 0) 
			nw = nd;
		nd = nd->nxt;
	}
	nd = nw;
	if(Inside_CELL(e, nd->x, nd->y) == BUTTON_SPRITE_MOUSE_DOWN) {
		ON_MOVE.x = ON_MOVE.y = ON_MOVE.id = SG_ABILITY_USE = 0;
		return true;
	}
	for(int i = 0; i <= CELL_WIDTH + 1; i++)
		for(int j = 0; j <= CELL_HEIGHT + 1; j++)
			dis[i][j] = CELL_WIDTH * CELL_HEIGHT;
	dis[nd->x][nd->y] = 0;
	for(int step = 0; step < CELL_WIDTH * CELL_HEIGHT; step++) {
		for(int i = 1; i <= CELL_WIDTH; i++) {
			for(int j = 1; j <= CELL_HEIGHT; j++) {
				if(gcell[i][j].house || gcell[i][j].light)
					continue;
				if(dis[i][j] > dis[i][j - 1])
					dis[i][j] = min(dis[i][j], dis[i][j - 1] + 1);
				if(dis[i][j] > dis[i][j + 1]) {
					dis[i][j] = min(dis[i][j], dis[i][j + 1] + 1);
				}
				if(i % 2 == 0) {
					if(dis[i][j] > dis[i - 1][j - 1])
						dis[i][j] = min(dis[i][j], dis[i - 1][j - 1] + 1);
					if(dis[i][j] > dis[i - 1][j])
						dis[i][j] = min(dis[i][j], dis[i - 1][j] + 1);	
					if(dis[i][j] > dis[i + 1][j - 1])
						dis[i][j] = min(dis[i][j], dis[i + 1][j - 1] + 1);
					if(dis[i][j] > dis[i + 1][j])
						dis[i][j] = min(dis[i][j], dis[i + 1][j] + 1);				
				}
				else {
					if(dis[i][j] > dis[i - 1][j + 1])
						dis[i][j] = min(dis[i][j], dis[i - 1][j + 1] + 1);
					if(dis[i][j] > dis[i - 1][j])
						dis[i][j] = min(dis[i][j], dis[i - 1][j] + 1);	
					if(dis[i][j] > dis[i + 1][j + 1])
						dis[i][j] = min(dis[i][j], dis[i + 1][j + 1] + 1);
					if(dis[i][j] > dis[i + 1][j])
						dis[i][j] = min(dis[i][j], dis[i + 1][j] + 1);						
				}
			}
		}
	}
	if(ON_MOVE.id != 0) {
		for(int i = 1; i <= CELL_WIDTH; i++) {
			for(int j = 1; j <= CELL_HEIGHT; j++) {
				if(dis[i][j] + dit[i][j] != dis[ON_MOVE.x][ON_MOVE.y] || dit[i][j] > 3 - SG_ABILITY_USE || IS_CHARECTER_IN(i, j) == true)
					continue;
				if(Inside_CELL(e, i, j) == BUTTON_SPRITE_MOUSE_DOWN) {
					SG_ABILITY_USE += dit[i][j];
					Change_Location(ON_MOVE.x, ON_MOVE.y, i, j);
					ON_MOVE.x = ON_MOVE.y = ON_MOVE.id = 0;
					if(SG_ABILITY_USE == 3)
						return true;
					return false;
				}
			}
		}
		return false;	
	}
	nw = gcharecter->nxt;
	while(nw != NULL) {
		if(strcmp(nw->str, "JW") != 0) {
			if(Inside_CELL(e, nw->x, nw->y) == BUTTON_SPRITE_MOUSE_DOWN) {
				ON_MOVE.x = nw->x, ON_MOVE.y = nw->y, ON_MOVE.id = 1;
				for(int i = 0; i <= CELL_WIDTH + 1; i++)
					for(int j = 0; j <= CELL_HEIGHT + 1; j++)
						dit[i][j] = CELL_WIDTH * CELL_HEIGHT;
				dit[nw->x][nw->y] = 0;
				for(int step = 0; step < CELL_WIDTH * CELL_HEIGHT; step++) {
					for(int i = 1; i <= CELL_WIDTH; i++) {
						for(int j = 1; j <= CELL_HEIGHT; j++) {
							if(gcell[i][j].house || gcell[i][j].light)
								continue;
							if(dit[i][j] > dit[i][j - 1])
								dit[i][j] = min(dit[i][j], dit[i][j - 1] + 1);
							if(dit[i][j] > dit[i][j + 1]) {
								dit[i][j] = min(dit[i][j], dit[i][j + 1] + 1);
							}
							if(i % 2 == 0) {
								if(dit[i][j] > dit[i - 1][j - 1])
									dit[i][j] = min(dit[i][j], dit[i - 1][j - 1] + 1);
								if(dit[i][j] > dit[i - 1][j])
									dit[i][j] = min(dit[i][j], dit[i - 1][j] + 1);	
								if(dit[i][j] > dit[i + 1][j - 1])
									dit[i][j] = min(dit[i][j], dit[i + 1][j - 1] + 1);
								if(dit[i][j] > dit[i + 1][j])
									dit[i][j] = min(dit[i][j], dit[i + 1][j] + 1);				
							}
							else {			
								if(dit[i][j] > dit[i - 1][j + 1])
									dit[i][j] = min(dit[i][j], dit[i - 1][j + 1] + 1);
								if(dit[i][j] > dit[i - 1][j])
									dit[i][j] = min(dit[i][j], dit[i - 1][j] + 1);	
								if(dit[i][j] > dit[i + 1][j + 1])
									dit[i][j] = min(dit[i][j], dit[i + 1][j + 1] + 1);
								if(dit[i][j] > dit[i + 1][j])
									dit[i][j] = min(dit[i][j], dit[i + 1][j] + 1);			
							}
						}
					}
				}
				return false;
			}
		}
		nw = nw->nxt;
	}
	return false;
}
