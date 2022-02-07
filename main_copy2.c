#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define ll long long
#define on true
#define off false
const int FPS = 60;

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

//hexagon dimension
const int HEXAGON_HEIGHT = 60;

//Cell dimension constants
int CELL_WIDTH;
int CELL_HEIGHT;
int HOUSE_NUMBER;
int LIGHT_NUMBER;
int HOLES_NUMBER;
int EXIT_NUMBER;
const int CHARECTER_NUMBER = 8;
const int MAX_CELL_WIDTH = 100;
const int MAX_CELL_HIGHT = 100;
const int MAX_LIGHT = 100 * 100;
const int MAX_HOLES = 100 * 100;
const int MAX_EXIT = 100 * 100;

//Button constants
const int BUTTON_WIDTH = 20;
const int BUTTON_HEIGHT = 40;
const int CBUTTON_WIGHT = 40;
const int CBUTTON_HEIGHT = 70;
const int MAX_BUTTONS = 100 * 100;
int TOTAL_BUTTONS;

// Jack visible
char LEVEL_STR[9][2] = {"0\0", "1\0", "2\0", "3\0", "4\0", "5\0", "6\0", "7\0", "8\0"};
bool Jack_Show;
bool BUTTON_END;
int LEVEL_NUM = 0;
int CART_NUM = 5;
char WHO_IS_JACK[3];

//Map buttons linked list
enum LBUTTON_SETIATION_SPRITE {
	IS_NOT_SELECT = 0, 
	IS_SELECTED_NOT_SELECT_SETIATION = 1,
	IS_SELECTED_AND_SELECT_ABILITY = 2,
	IS_SELECTED_AND_SELECT_MOVE = 3,
	IS_SELECTED_MOVE_WAIT_FOR_ABILITY = 4,
	IS_SELECTED_ABILITY_WAIT_FOR_MOVE = 5,
	IS_DONE = 6,
	NUMEBER_IS = 7
};

//استراکت کارکتر ها
struct Linked_List {
	char str[3];
	short int x, y;
	enum  LBUTTON_SETIATION_SPRITE BUTTON_SETIATION; 
	struct Linked_List* nxt;
};

struct Linked_List* gcharecter;
struct Linked_List* Section1;
struct Linked_List* Section2;
struct Linked_List* Base;

//تعریف استراکت برای چراغ ها چاه ها و خروجی ها 
typedef struct {
	short int x, y;
	bool sit;
} SLighstHolesExits;

// این برای سهولت در استفاده از کارکتر ها است

// استراکت خونه ها
typedef struct {
	short int vx[7], vy[7];
	bool house;
	bool light;
	bool hole;
	bool exit;
} cell;

// تعریف خونه ها طبق دستور کار
cell gcell[MAX_CELL_WIDTH][MAX_CELL_HIGHT];

// تعریف چاه ها و چراغ ها و خروجی ها
SLighstHolesExits glight[MAX_LIGHT], ghole[MAX_HOLES], gexit[MAX_EXIT];


TTF_Font* gFont;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


enum LButtonSprite {
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

enum LButtonSprite Inside(SDL_Event* e, int xb, int yb, int wb, int hb) {
	//Get mouse position
	int x, y;
	SDL_GetMouseState( &x, &y );
	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if(x < xb) {
		inside = false;
	}
	//Mouse is right of the button
	else if(x > xb + wb) {
		inside = false;
	}
	//Mouse above the button
	else if(y < yb) {
		inside = false;
	}
	//Mouse below the button
	else if(y > yb + hb) {
		inside = false;
	}
	//Mouse is outside button
	if(!inside) {
		return BUTTON_SPRITE_MOUSE_OUT;
	}
	//Mouse is inside button
	else {
		//Set mouse over sprite
		switch(e->type) {
			case SDL_MOUSEMOTION:
				return BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
		
			case SDL_MOUSEBUTTONDOWN:
				return BUTTON_SPRITE_MOUSE_DOWN;
				break;
				
			case SDL_MOUSEBUTTONUP:
				return BUTTON_SPRITE_MOUSE_UP;
				break;
		}
	}
	return BUTTON_SPRITE_MOUSE_OUT;
} 

struct Move_Plans{
	int x, y;
	bool JACK_Capture;
	struct Move_Plans* nxt;
};

struct Move_Plans* rt;

bool Is_In_Move[MAX_CELL_WIDTH][MAX_CELL_HIGHT];

void Print(char *st, int x, int y, int texW, int texH, SDL_Color color) {
 	SDL_Surface* surface = TTF_RenderText_Solid(gFont, st, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
   	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {x, y, texW, texH };
	SDL_RenderCopy(gRenderer, texture, NULL, &dstrect);	
}

void DETECTIVE_WIN() {
	int cnt = 1e9;
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
		char t[70] = "DETECTIVE WIN OOOOOOOOO HOOOOOOO OOOOOOO JACK LOSE OOOOOOO **********\0";
		SDL_Color color = {0, 0, 0};
		Print(t, 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, color);	
		SDL_RenderPresent(gRenderer);
  		SDL_Delay(1000/FPS);
  	}
}

void JACK_WIN() {
	int cnt = 1e9;
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
		char t[70] = "JACK WIN OOOOOOOOO HOOOOOOO OOOOOOO DETECTIVE LOSE OOOOOOO **********\0";
		SDL_Color color = {0, 0, 0};
		Print(t, 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, color);	
		SDL_RenderPresent(gRenderer);
  		SDL_Delay(1000/FPS);
  	}
}

enum LButtonSprite Inside_TRIANGLE(SDL_Event* e, int x1, int y1, int x2, int y2, int x3, int y3) {
	int xm, ym;
	SDL_GetMouseState(&xm, &ym);
	double x[4] = {x1, x2, x3, xm};
	double y[4] = {y1, y2, y3, ym};
	double d[4][4], sum[4];
	int c[4];
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			d[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
		}
	}
	for(int f = 0; f < 4; f++) {
		double pi = 0;
		int k = 0;
		for(int i = 0; i < 4; i++)
			if(i != f)
				c[k++] = i;
		for(int i = 0; i < k; i++)
			for(int j = i + 1; j < k; j++)
				pi = pi + d[c[i]][c[j]];
		pi /= 2;
		sum[f] = pi;
		for(int i = 0; i < k; i++)
			for(int j = i + 1; j < k; j++)
				sum[f] = sum[f] * (pi - d[c[i]][c[j]]);
		sum[f] = fmax((double)0, sum[f]);
		sum[f] = sqrt(sum[f]);
	}
	double h = sum[3] - sum[0] - sum[1] - sum[2];
	if(fabs(sum[3] - (sum[0] + sum[1] + sum[2])) < 0.0000001) {
		//Set mouse over sprite
		switch(e->type) {
			case SDL_MOUSEMOTION:
				return BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
		
			case SDL_MOUSEBUTTONDOWN:
				return BUTTON_SPRITE_MOUSE_DOWN;
				break;
				
			case SDL_MOUSEBUTTONUP:
				return BUTTON_SPRITE_MOUSE_UP;
				break;
		}
	}
	return BUTTON_SPRITE_MOUSE_OUT;
}

void Lets_Go_End(int i, int j) {
	struct Linked_List* nd = gcharecter;
	struct Linked_List* nw;
	while(nd != NULL) {
		if(nd->x == i && nd->y == j) {
			nw = nd;
			break;
		}
		nd = nd->nxt;
	}	
	if(strcmp(WHO_IS_JACK, nd->str) == 0) 
		DETECTIVE_WIN();
	else
		JACK_WIN();
	return;
}

bool IS_CHARECTER_IN(int x, int y) {
	struct Linked_List* nd = gcharecter;
	while(nd != NULL) {
		if(nd->x == x && nd->y == y) 
			return true;
		nd = nd->nxt;
	}	
	return false;
}

void Normal_Move() {
	for(int i = 1; i <= CELL_WIDTH; i++) 
		for(int j = 1; j <= CELL_WIDTH; j++) 
			Is_In_Move[i][j] = false;
	Is_In_Move[rt->x][rt->y] = true;
	for(int k = 1; k <= 3; k++) {
		for(int i = 1; i <= CELL_WIDTH; i++) {
			for(int j = 1; j <= CELL_WIDTH; j++) {
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
					if(i != j && ghole[j].sit && Is_In_Move[ghole[i].x][ghole[i].y] == false) {
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
		for(int j = 1; j <= CELL_WIDTH; j++) 
			Is_In_Move[i][j] = false;
	Is_In_Move[rt->x][rt->y] = true;
	for(int k = 1; k <= 3; k++) {
		for(int i = 1; i <= CELL_WIDTH; i++) {
			for(int j = 1; j <= CELL_WIDTH; j++) {
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
					if(i != j && ghole[j].sit && Is_In_Move[ghole[i].x][ghole[i].y] == false) {
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

void Change_Location(int x, int y, int i, int j) {
	struct Linked_List* nd = gcharecter;
	while(nd != NULL) {
		if(nd->x == x && nd->y == y) {
			nd->x = i;
			nd->y = j;
			printf("%s %d %d\n", nd->str, nd->x, nd->y);
			return;
		}
		nd = nd->nxt;
	}	
	return;
}

void handleEvent(SDL_Event* e) {
	//If mouse event happened
	if(e->type != SDL_MOUSEMOTION && e->type != SDL_MOUSEBUTTONDOWN && e->type != SDL_MOUSEBUTTONUP) {
		return;
	}
	int cnt = 1, cnn = 1;
	struct Linked_List* nd = Base->nxt;
	struct Linked_List* nw = Base;
	enum LBUTTON_SETIATION_SPRITE IS_SOME_BUTTON_SELECT = IS_NOT_SELECT;
	while(nd != NULL) {
		if(nd->BUTTON_SETIATION != IS_DONE && nd->BUTTON_SETIATION != IS_NOT_SELECT) {
			IS_SOME_BUTTON_SELECT = nd->BUTTON_SETIATION;
			nw = nd;
			cnn = cnt;
		}
		cnt++;
		nd = nd->nxt;
	}
	if(IS_SOME_BUTTON_SELECT == IS_NOT_SELECT) {
		nd = Base->nxt;
		int cnt = 1;
		while(nd != NULL) {
			enum LButtonSprite BMod = Inside(e, SCREEN_WIDTH - 3 * HEXAGON_HEIGHT, cnt * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2, CBUTTON_WIGHT, CBUTTON_HEIGHT);
			if(nd->BUTTON_SETIATION == IS_NOT_SELECT && BMod == BUTTON_SPRITE_MOUSE_DOWN) 
				nd->BUTTON_SETIATION = IS_SELECTED_NOT_SELECT_SETIATION;
			cnt++;
			nd = nd->nxt;
		}
		return;
	}
	int x1 = SCREEN_WIDTH - 3 * HEXAGON_HEIGHT + CBUTTON_WIGHT + HEXAGON_HEIGHT / 4, y1 = cnn * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2;
	int x2 = x1, y2 = y1 + CBUTTON_HEIGHT / 2 + 2;
	if(IS_SOME_BUTTON_SELECT == IS_SELECTED_NOT_SELECT_SETIATION) {
	//	printf("WTF\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		enum LButtonSprite BMod = Inside(e, x1, y1, SCREEN_WIDTH - x1, CBUTTON_HEIGHT / 2 - 2);
		enum LButtonSprite BMod2 = Inside(e, x2, y2, SCREEN_WIDTH - x2, CBUTTON_HEIGHT / 2 - 2);
		if(BMod == BUTTON_SPRITE_MOUSE_DOWN) {
			rt = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
			nw->BUTTON_SETIATION = IS_SELECTED_AND_SELECT_MOVE;
			rt->nxt = NULL;
			rt->x = nw->x;
			rt->y = nw->y;
			if(strcmp(nw->str, "MS") != 0) 
				Normal_Move();
			else
				MS_MOVE();
		}
		else if(BMod2 == BUTTON_SPRITE_MOUSE_DOWN) {
			if(strcmp(nw->str, "SH") == 0 || strcmp(nw->str, "JW") == 0 || strcmp(nw->str, "IL") == 0)
				return;
			nw->BUTTON_SETIATION = IS_SELECTED_AND_SELECT_ABILITY;
		}
		return;
	}
	if(IS_SOME_BUTTON_SELECT == IS_SELECTED_AND_SELECT_MOVE) {
		struct Move_Plans* np = rt->nxt;
		while(np != NULL) {
			int i = np->x, j = np->y;
			enum LButtonSprite BMod = Inside(e, gcell[i][j].vx[0], gcell[i][j].vy[0], BUTTON_WIDTH, BUTTON_HEIGHT);
			enum LButtonSprite BMod2 = Inside_TRIANGLE(e, gcell[i][j].vx[0], gcell[i][j].vy[0], gcell[i][j].vx[5], gcell[i][j].vy[5], gcell[i][j].vx[4], gcell[i][j].vy[4]);
			enum LButtonSprite BMod3 = Inside_TRIANGLE(e, gcell[i][j].vx[1], gcell[i][j].vy[1], gcell[i][j].vx[2], gcell[i][j].vy[2], gcell[i][j].vx[3], gcell[i][j].vy[3]);
			//printf("%d %d %d\n", i, j, BMod);
			if(BMod == BUTTON_SPRITE_MOUSE_DOWN || BMod2 == BUTTON_SPRITE_MOUSE_DOWN || BMod3 == BUTTON_SPRITE_MOUSE_DOWN) {
				if(IS_CHARECTER_IN(i, j) == true) {
					BUTTON_END = true;
					Lets_Go_End(i, j);
					return;
				}
				else {
					Change_Location(nw->x, nw->y, i, j);
					printf("%d %d %d %d %d\n", i, j, BMod, BMod2, BMod3);
					nw->x = i, nw->y = j;
					if(strcmp(nw->str, "MS") == 0 || strcmp(nw->str, "WG") == 0) {
						nw->BUTTON_SETIATION = IS_DONE;
						CART_NUM++;
						return;
					}
					nw->BUTTON_SETIATION = IS_DONE;
						CART_NUM++;
					return;
				}	
			}
			np = np->nxt;
		}
	}
	if(IS_SOME_BUTTON_SELECT == IS_SELECTED_AND_SELECT_ABILITY) {
			
	}
}

void Draw_Circule(short int x, short int y, int radius, int cr, int cg, int cb, int ca) {
	SDL_SetRenderDrawColor(gRenderer, cr, cg, cb, ca);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(gRenderer, x + dx, y + dy);
            }
        }
    }
}

void Build_Show_Buttons() {
	CART_NUM = 1;
	LEVEL_NUM++;
	if(LEVEL_NUM % 2 == 0) {
		Base = Section2;
		return;
	}
	bool Is_In_Section[CHARECTER_NUMBER];
	for(int i = 0; i < CHARECTER_NUMBER; i++)
		Is_In_Section[i] = false;
	Section1 = (struct Linked_List*)malloc(sizeof(struct Linked_List));
	Section2 = (struct Linked_List*)malloc(sizeof(struct Linked_List));
	Section1->nxt = NULL;
	Section2->nxt = NULL;
	for(int i = 0; i < CHARECTER_NUMBER / 2; i++) {
		int cnt = rand() % (CHARECTER_NUMBER - i) + 1;
		int wh = 0;
		struct Linked_List* nd = gcharecter->nxt;
		while(cnt && nd != NULL) {
			if(Is_In_Section[wh] == false)
				cnt--;
			if(Is_In_Section[wh] == false && cnt == 0) {
				struct Linked_List* nw = (struct Linked_List*)malloc(sizeof(struct Linked_List));
				strcpy(nw->str, nd->str);
				nw->x = nd->x;
				nw->y = nd->y;
				nw->BUTTON_SETIATION = IS_NOT_SELECT;
				nw->nxt = Section1->nxt;
				Section1->nxt = nw;
				Is_In_Section[wh] = true;
				break;
			}
			nd = nd->nxt;
			wh++;
		}
	}
	int wh = 0;
	struct Linked_List* nd = gcharecter->nxt;
	nd = gcharecter->nxt;
	while(nd != NULL) {
		if(Is_In_Section[wh] == false) {
			struct Linked_List* nw = (struct Linked_List*)malloc(sizeof(struct Linked_List));
			strcpy(nw->str, nd->str);
			nw->x = nd->x;
			nw->y = nd->y;
			nw->BUTTON_SETIATION = IS_NOT_SELECT;
			nw->nxt = Section2->nxt;
			Section2->nxt = nw;
			Is_In_Section[wh] = true;
		}
		nd = nd->nxt; 
		wh++;			
	}
	Base = Section1;
}

void JMap_Render() {
	for(int i = 1; i <= CELL_WIDTH; i++) {
		for(int j = 1; j <= CELL_HEIGHT; j++) {
			filledPolygonRGBA(gRenderer, gcell[i][j].vx, gcell[i][j].vy, 6, 157, 139, 124, 255);
			if(gcell[i][j].house == true) {
				aatrigonRGBA(gRenderer, gcell[i][j].vx[5] + HEXAGON_HEIGHT / 4, gcell[i][j].vy[5]
					,gcell[i][j].vx[2] - HEXAGON_HEIGHT / 4, gcell[i][j].vy[5]
					,gcell[i][j].vx[0] + HEXAGON_HEIGHT / 4, gcell[i][j].vy[0] + 1,
					255, 0, 0, 255
				);
				boxRGBA(gRenderer, gcell[i][j].vx[5] + HEXAGON_HEIGHT / 4, gcell[i][j].vy[5], gcell[i][j].vx[3], gcell[i][j].vy[3] - 1, 80, 83, 129, 150);
			}
			if(gcell[i][j].exit == true) {
				boxRGBA(gRenderer, gcell[i][j].vx[0] + 1, gcell[i][j].vy[0] + 1, gcell[i][j].vx[3] - 1, gcell[i][j].vy[3] - 1, 63, 123, 23, 150);
			}	
			if(gcell[i][j].hole == true) {
				Draw_Circule(gcell[i][j].vx[5] + HEXAGON_HEIGHT / 2, gcell[i][j].vy[5], HEXAGON_HEIGHT / 4, 80, 80, 80, 250);
			}
			if(gcell[i][j].light == true) {
				Draw_Circule(gcell[i][j].vx[5] + HEXAGON_HEIGHT / 2, gcell[i][j].vy[5], HEXAGON_HEIGHT / 4, 255, 255, 0, 100);
			}		
			for(int k = 0; k < 6; k++) 
				aalineRGBA(gRenderer, gcell[i][j].vx[k], gcell[i][j].vy[k], gcell[i][j].vx[(k + 1) % 6], gcell[i][j].vy[(k + 1) % 6], 255, 255, 255, 100);
		}
	}

	struct Linked_List* nd = gcharecter->nxt;
	while(nd != NULL) {
		SDL_Color color = { 255, 255, 255 };
//		printf("%s %d %d\n", nd->str, nd->x, nd->y);
		Print(nd->str, gcell[nd->x][nd->y].vx[0], gcell[nd->x][nd->y].vy[0] + HEXAGON_HEIGHT / 4, HEXAGON_HEIGHT / 4, HEXAGON_HEIGHT / 4, color);
		nd = nd->nxt;
	}

	if(Jack_Show) {
		boxRGBA(gRenderer, SCREEN_WIDTH - 4 * HEXAGON_HEIGHT, HEXAGON_HEIGHT / 4, SCREEN_WIDTH - HEXAGON_HEIGHT, HEXAGON_HEIGHT * 5 / 4, 255, 255, 51, 128);
		SDL_Color color = {255, 255, 255};
		char t[15] = "Jack is Visible";
		Print(t, SCREEN_WIDTH - 4 * HEXAGON_HEIGHT + HEXAGON_HEIGHT / 4, HEXAGON_HEIGHT / 2, HEXAGON_HEIGHT / 2, HEXAGON_HEIGHT / 2, color);
	}
	else {
		boxRGBA(gRenderer, SCREEN_WIDTH - 4 * HEXAGON_HEIGHT, HEXAGON_HEIGHT / 4, SCREEN_WIDTH - HEXAGON_HEIGHT, HEXAGON_HEIGHT * 5 / 4, 128, 128, 128, 128);
		SDL_Color color = {0, 0, 0};
		char t[17] = "Jack is InVisible";
		Print(t, SCREEN_WIDTH - 4 * HEXAGON_HEIGHT + HEXAGON_HEIGHT / 4, HEXAGON_HEIGHT / 2, HEXAGON_HEIGHT / 2, HEXAGON_HEIGHT / 2, color);
	}

	boxRGBA(gRenderer, SCREEN_WIDTH - HEXAGON_HEIGHT + HEXAGON_HEIGHT / 4, HEXAGON_HEIGHT / 4, SCREEN_WIDTH - HEXAGON_HEIGHT / 4, HEXAGON_HEIGHT * 5 / 4, 255, 165, 0, 150);
	SDL_Color color = {255, 255, 255};
	Print(LEVEL_STR[LEVEL_NUM], SCREEN_WIDTH - HEXAGON_HEIGHT + HEXAGON_HEIGHT / 4 * 1.7, HEXAGON_HEIGHT / 4 * 1.9, HEXAGON_HEIGHT / 2, HEXAGON_HEIGHT / 2, color);

	int cnt = 1;
	nd = Base->nxt;
	while(nd != NULL) {
		if(nd->BUTTON_SETIATION == IS_NOT_SELECT) {
//			printf("cnt = %d\n", cnt);
			boxRGBA(gRenderer, SCREEN_WIDTH - 3 * HEXAGON_HEIGHT, cnt * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2, SCREEN_WIDTH - 3 * HEXAGON_HEIGHT + CBUTTON_WIGHT, cnt * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2 + CBUTTON_HEIGHT, 160, 255, 47, 255);
			SDL_Color color = {0, 0, 0};
			Print(nd->str, SCREEN_WIDTH - 3 * HEXAGON_HEIGHT + 0.05 * HEXAGON_HEIGHT, cnt * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2 + 0.4 * HEXAGON_HEIGHT, CBUTTON_WIGHT, CBUTTON_HEIGHT, color);		
		}
		else { 
			boxRGBA(gRenderer, SCREEN_WIDTH - 3 * HEXAGON_HEIGHT, cnt * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2, SCREEN_WIDTH - 3 * HEXAGON_HEIGHT + CBUTTON_WIGHT, cnt * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2 + CBUTTON_HEIGHT, 255, 47, 154, 255);
			SDL_Color color = {0, 0, 0};
			Print(nd->str, SCREEN_WIDTH - 3 * HEXAGON_HEIGHT + 0.05 * HEXAGON_HEIGHT, cnt * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2 + 0.4 * HEXAGON_HEIGHT, CBUTTON_WIGHT, CBUTTON_HEIGHT, color);			
		}
		if(nd->BUTTON_SETIATION != IS_DONE && nd->BUTTON_SETIATION != IS_NOT_SELECT) {
			int x1 = SCREEN_WIDTH - 3 * HEXAGON_HEIGHT + CBUTTON_WIGHT + HEXAGON_HEIGHT / 4, y1 = cnt * HEXAGON_HEIGHT * 2 + HEXAGON_HEIGHT / 2;
			int x2 = x1, y2 = y1 + CBUTTON_HEIGHT / 2 + 2;
			boxRGBA(gRenderer, x1, y1, SCREEN_WIDTH, y1 + CBUTTON_HEIGHT / 2 - 2, 160, 255, 47, 255);
			boxRGBA(gRenderer, x2, y2, SCREEN_WIDTH, y2 + CBUTTON_HEIGHT / 2 - 2, 160, 255, 47, 255);
		}
		if(nd->BUTTON_SETIATION == IS_SELECTED_AND_SELECT_MOVE) {
			struct Move_Plans* nw = rt->nxt;
			while(nw != NULL) {
				int i = nw->x, j = nw->y;
				if(nw->JACK_Capture == false) {
					filledPolygonRGBA(gRenderer, gcell[i][j].vx, gcell[i][j].vy, 6, 28, 57, 187, 100);
				}
				else {
					filledPolygonRGBA(gRenderer, gcell[i][j].vx, gcell[i][j].vy, 6, 255, 0, 0, 100);				
				}
				for(int k = 0; k < 6; k++) 
					aalineRGBA(gRenderer, gcell[i][j].vx[k], gcell[i][j].vy[k], gcell[i][j].vx[(k + 1) % 6], gcell[i][j].vy[(k + 1) % 6], 255, 255, 255, 100);
				nw = nw->nxt;
			}
		}
		cnt++;
		nd = nd->nxt;
	}
}

void Input() {

	FILE *fpin;
	fpin = fopen("jmap.txt", "r");
	if(fpin == NULL){
		printf("Cannot open %s\n", "jmap.txt");
		return;
	}
	
	fscanf(fpin, "%d %d", &CELL_WIDTH, &CELL_HEIGHT);
	//
	SCREEN_WIDTH = 5 * HEXAGON_HEIGHT + HEXAGON_HEIGHT / 2 * CELL_WIDTH + HEXAGON_HEIGHT / 2 * ((CELL_WIDTH + 1) / 2); 
	SCREEN_HEIGHT = 2 * HEXAGON_HEIGHT + HEXAGON_HEIGHT * CELL_HEIGHT;
	//
	TOTAL_BUTTONS = CELL_WIDTH * CELL_HEIGHT;
	for(int i = 1; i <= CELL_WIDTH; i++) {
		for(int j = 1; j <= CELL_HEIGHT; j++) {
			if(i % 2 == 0) {
				gcell[i][j].vx[0] = HEXAGON_HEIGHT + (i / 2) * HEXAGON_HEIGHT + ((i - 1) / 2) * HEXAGON_HEIGHT / 2; 
				gcell[i][j].vy[0] = HEXAGON_HEIGHT + (j - 1) * HEXAGON_HEIGHT;
			}
			else {
				gcell[i][j].vx[0] = HEXAGON_HEIGHT * 5 / 4 + (i / 2) * HEXAGON_HEIGHT + (i / 2) * HEXAGON_HEIGHT / 2; 
				gcell[i][j].vy[0] = HEXAGON_HEIGHT * 6 / 4 + (j - 1) * HEXAGON_HEIGHT;
			}
			gcell[i][j].vx[1] = gcell[i][j].vx[0] + HEXAGON_HEIGHT / 2;
			gcell[i][j].vy[1] = gcell[i][j].vy[0];
			gcell[i][j].vx[2] = gcell[i][j].vx[0] + HEXAGON_HEIGHT * 3 / 4;
			gcell[i][j].vy[2] = gcell[i][j].vy[0] + HEXAGON_HEIGHT / 2;
			gcell[i][j].vx[3] = gcell[i][j].vx[0] + HEXAGON_HEIGHT / 2;
			gcell[i][j].vy[3] = gcell[i][j].vy[0] + HEXAGON_HEIGHT;
			gcell[i][j].vx[4] = gcell[i][j].vx[0];
			gcell[i][j].vy[4] = gcell[i][j].vy[0] + HEXAGON_HEIGHT;
			gcell[i][j].vx[5] = gcell[i][j].vx[0] - HEXAGON_HEIGHT / 4;
			gcell[i][j].vy[5] = gcell[i][j].vy[0] + HEXAGON_HEIGHT / 2;
		}
	}

	//
	fscanf(fpin, "%d", &HOUSE_NUMBER);
	for(int k = 0; k < HOUSE_NUMBER; k++) {
		int x, y;
		fscanf(fpin, "%d %d", &x, &y);
		gcell[x][y].house = true;
	}

	//
	fscanf(fpin, "%d", &LIGHT_NUMBER);
	for(int k = 0; k < LIGHT_NUMBER; k++) {
		int xx, yy, z;
		fscanf(fpin, "%d %d %d", &xx, &yy, &z);
		gcell[xx][yy].light = true;
		glight[k].x = xx;
		glight[k].y = yy;
		glight[k].sit = z;
	}

	//
	fscanf(fpin, "%d", &HOLES_NUMBER);
	for(int k = 0; k < HOLES_NUMBER; k++) {
		int xx, yy, z;
		fscanf(fpin, "%d %d %d", &xx, &yy, &z);
		gcell[xx][yy].hole = true;
		ghole[k].x = xx;
		ghole[k].y = yy;
		ghole[k].sit = z;
	}	
	gcharecter = (struct Linked_List*)malloc(sizeof(struct Linked_List));
	gcharecter->nxt = NULL;
	//
	for(int i = 0; i < CHARECTER_NUMBER; i++) {
		struct Linked_List* nw = (struct Linked_List*)malloc(sizeof(struct Linked_List));
		fscanf(fpin, "%s", nw->str);
		fscanf(fpin, "%hd %hd", &nw->x, &nw->y);
		nw->nxt = gcharecter->nxt;
		gcharecter->nxt = nw;
	}
	//
	fscanf(fpin, "%d", &EXIT_NUMBER);
	for(int k = 0; k < EXIT_NUMBER; k++) {
		int xx, yy, z;
		fscanf(fpin, "%d %d %d", &xx, &yy, &z);		
		gcell[xx][yy].exit = true;
		gexit[k].x = xx;
		gexit[k].y = yy;
		gexit[k].sit = z;		
	}
	//
	fclose(fpin);
}

void close() {
	//Free loaded images
//	gButtonSpriteSheetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_CloseFont(gFont);
	TTF_Quit();
	SDL_Quit();
}

int main() {
	srand(time(NULL));
	Input();
	TTF_Init();
	gFont = TTF_OpenFont( "IRNazanin.ttf", 28);
	if(gFont == NULL) {
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		return 0;
	}
	if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return 0;
	}
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf( "Warning: Linear texture filtering not enabled!" );
		return 0;
	}
	gWindow = SDL_CreateWindow( "Mohammad Hosseini Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );	
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	while (BUTTON_END == false) {
  		SDL_SetRenderDrawColor(gRenderer, 102, 94, 76, 0);
  		SDL_RenderClear(gRenderer);
  		SDL_Event sdlEvent;
  		int SHUTDOWNCODE=0;
	    while (SDL_PollEvent(&sdlEvent)) {
	        if (sdlEvent.type==SDL_QUIT) {
	            SHUTDOWNCODE=1;
	            break;
	        }
			handleEvent(&sdlEvent);
	    }
	    if (SHUTDOWNCODE) break;
		if(CART_NUM == 5) 
			Build_Show_Buttons();
		JMap_Render();
		SDL_RenderPresent(gRenderer);
  		SDL_Delay(1000/FPS);
  	}
	//Free resources and close SDL
	close();
	return 0; 
}