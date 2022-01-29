
void Save() {
	FILE *fpout;
	fpout = fopen("save.txt", "wb");
	fwrite(&SCREEN_WIDTH, sizeof(int), 1, fpout);
	fwrite(&SCREEN_HEIGHT, sizeof(int), 1, fpout);
	fwrite(&CELL_WIDTH, sizeof(int), 1, fpout);
	fwrite(&CELL_HEIGHT, sizeof(int), 1, fpout);
	fwrite(&HOUSE_NUMBER, sizeof(int), 1, fpout);
	fwrite(&LIGHT_NUMBER, sizeof(int), 1, fpout);
	fwrite(&HOLES_NUMBER, sizeof(int), 1, fpout);
	fwrite(&EXIT_NUMBER, sizeof(int), 1, fpout);
	fwrite(&TOTAL_BUTTONS, sizeof(int), 1, fpout);
	fwrite(&Jack_Show, sizeof(bool), 1, fpout);
	fwrite(&BUTTON_END, sizeof(bool), 1, fpout);
	fwrite(&LEVEL_NUM, sizeof(int), 1, fpout);
	fwrite(&CART_NUM, sizeof(int), 1, fpout);
	fwrite(&WHO_IS_JACK, 3 * sizeof(char), 1, fpout);
	fwrite(&JW_LIGHT, sizeof(enum JW_LIGHT_SITUATION), 1, fpout);
	fwrite(&SG_ABILITY_USE, sizeof(int), 1, fpout);
	fwrite(&ON_MOVE, sizeof(JS_IL_JB_ABIULITY), 1, fpout);
	fwrite(&dis, sizeof(dis), 1, fpout);
	fwrite(&dit, sizeof(dis), 1, fpout);
	fwrite(&JS_SITUATION, sizeof(JS_IL_JB_ABIULITY), 1, fpout);
	fwrite(&IL_SITUATION, sizeof(JS_IL_JB_ABIULITY), 1, fpout);
	fwrite(&JB_SITUATION, sizeof(JS_IL_JB_ABIULITY), 1, fpout);
	int sz = 0;
	struct Linked_List* nd = gcharecter->nxt;
	while(nd != NULL) {
		sz++;
		nd = nd->nxt;
	}
	nd = gcharecter->nxt;
	fwrite(&sz, sizeof(int), 1, fpout);
	while(nd != NULL) {
		fwrite(&nd, sizeof(struct Linked_List), 1, fpout);
		nd = nd->nxt;
	}
	sz = 0;
	nd = SHcharecter->nxt;
	while(nd != NULL) {
		sz++;
		nd = nd->nxt;
	}
	nd = SHcharecter->nxt;
	fwrite(&sz, sizeof(int), 1, fpout);
	while(nd != NULL) {
		fwrite(&nd, sizeof(struct Linked_List), 1, fpout);
		nd = nd->nxt;
	}
	sz = 0;
	nd = Section1->nxt;
	while(nd != NULL) {
		sz++;
		nd = nd->nxt;
	}
	nd = Section1->nxt;
	fwrite(&sz, sizeof(int), 1, fpout);
	while(nd != NULL) {
		fwrite(&nd, sizeof(struct Linked_List), 1, fpout);
		nd = nd->nxt;
	}
	sz = 0;
	nd = Section2->nxt;
	while(nd != NULL) {
		sz++;
		nd = nd->nxt;
	}
	nd = Section2->nxt;
	fwrite(&sz, sizeof(int), 1, fpout);
	while(nd != NULL) {
		fwrite(&nd, sizeof(struct Linked_List), 1, fpout);
		nd = nd->nxt;
	}
	sz = 0;
	nd = Base->nxt;
	while(nd != NULL) {
		sz++;
		nd = nd->nxt;
	}
	nd = Base->nxt;
	fwrite(&sz, sizeof(int), 1, fpout);
	while(nd != NULL) {
		fwrite(&nd, sizeof(struct Linked_List), 1, fpout);
		nd = nd->nxt;
	}
	fwrite(&gcell, sizeof(gcell), 1, fpout);
	fwrite(&glight, sizeof(glight), 1, fpout);
	fwrite(&ghole, sizeof(ghole), 1, fpout);
	fwrite(&gexit, sizeof(gexit), 1, fpout);
	sz = 0;
	struct Move_Plans* nw = rt->nxt;
	while(nw != NULL) {
		sz++;
		nw = nw->nxt;
	}
	nw = rt->nxt;
	fwrite(&sz, sizeof(int), 1, fpout);
	while(nw != NULL) {
		fwrite(&nw, sizeof(struct Move_Plans), 1, fpout);
		nw = nw->nxt;
	}
	fwrite(&Is_In_Move, sizeof(Is_In_Move), 1, fpout);
	fclose(fpout);
}

void Load() {
	FILE *fpin;
	fpin = fopen("save.txt", "rb");
	fread(&SCREEN_WIDTH, sizeof(int), 1, fpin);
	fread(&SCREEN_HEIGHT, sizeof(int), 1, fpin);
	fread(&CELL_WIDTH, sizeof(int), 1, fpin);
	fread(&CELL_HEIGHT, sizeof(int), 1, fpin);
	fread(&HOUSE_NUMBER, sizeof(int), 1, fpin);
	fread(&LIGHT_NUMBER, sizeof(int), 1, fpin);
	fread(&HOLES_NUMBER, sizeof(int), 1, fpin);
	fread(&EXIT_NUMBER, sizeof(int), 1, fpin);
	fread(&TOTAL_BUTTONS, sizeof(int), 1, fpin);
	fread(&Jack_Show, sizeof(bool), 1, fpin);
	fread(&BUTTON_END, sizeof(bool), 1, fpin);
	fread(&LEVEL_NUM, sizeof(int), 1, fpin);
	fread(&CART_NUM, sizeof(int), 1, fpin);
	fread(&WHO_IS_JACK, 3 * sizeof(char), 1, fpin);
	fread(&JW_LIGHT, sizeof(enum JW_LIGHT_SITUATION), 1, fpin);
	fread(&SG_ABILITY_USE, sizeof(int), 1, fpin);
	fread(&ON_MOVE, sizeof(JS_IL_JB_ABIULITY), 1, fpin);
	fread(&dis, sizeof(dis), 1, fpin);
	fread(&dit, sizeof(dis), 1, fpin);
	fread(&JS_SITUATION, sizeof(JS_IL_JB_ABIULITY), 1, fpin);
	fread(&IL_SITUATION, sizeof(JS_IL_JB_ABIULITY), 1, fpin);
	fread(&JB_SITUATION, sizeof(JS_IL_JB_ABIULITY), 1, fpin);
	int sz = 0;
	struct Linked_List* nd = gcharecter;
	fread(&sz, sizeof(int), 1, fpin);
	while(sz--) {
		struct Linked_List* nw = (struct Linked_List*)malloc(sizeof(struct Linked_List));
		fwrite(&nw, sizeof(struct Linked_List), 1, fpin);
		nd->nxt = nw;
		nd = nw;
	}
	sz = 0;
	nd = SHcharecter;
	fread(&sz, sizeof(int), 1, fpin);
	while(sz--) {
		struct Linked_List* nw = (struct Linked_List*)malloc(sizeof(struct Linked_List));
		fwrite(&nw, sizeof(struct Linked_List), 1, fpin);
        printf("%s\n", nw->str);
		nw->nxt = NULL;
		nd->nxt = nw;
		nd = nw;
	}
	sz = 0;
	nd = Section1;
	fread(&sz, sizeof(int), 1, fpin);
	while(sz--) {
		struct Linked_List* nw = (struct Linked_List*)malloc(sizeof(struct Linked_List));
		fwrite(&nw, sizeof(struct Linked_List), 1, fpin);
		nw->nxt = NULL;
		nd->nxt = nw;
		nd = nw;
	}
	sz = 0;
	nd = Section2;
	fread(&sz, sizeof(int), 1, fpin);
	while(sz--) {
		struct Linked_List* nw = (struct Linked_List*)malloc(sizeof(struct Linked_List));
		fwrite(&nw, sizeof(struct Linked_List), 1, fpin);
		nw->nxt = NULL;

		nd->nxt = nw;
		nd = nw;
	}
	sz = 0;
	nd = Base;
	fread(&sz, sizeof(int), 1, fpin);
	while(sz--) {
		struct Linked_List* nw = (struct Linked_List*)malloc(sizeof(struct Linked_List));
		fwrite(&nw, sizeof(struct Linked_List), 1, fpin);
		nw->nxt = NULL;

		nd->nxt = nw;
		nd = nw;
	}
	fread(&gcell, sizeof(gcell), 1, fpin);
	fread(&glight, sizeof(glight), 1, fpin);
	fread(&ghole, sizeof(ghole), 1, fpin);
	fread(&gexit, sizeof(gexit), 1, fpin);
	sz = 0;
	rt = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
	rt->nxt = NULL;
	struct Move_Plans* nw = rt;
	fread(&sz, sizeof(int), 1, fpin);
	while(sz--) {
		struct Move_Plans* nf = (struct Move_Plans*)malloc(sizeof(struct Move_Plans));
		fwrite(&nf, sizeof(struct Move_Plans), 1, fpin);
		nf->nxt = NULL;
		nw->nxt = nf;
		nw = nf;
	}
	fread(&Is_In_Move, sizeof(Is_In_Move), 1, fpin);
	fclose(fpin);
}

void MENU() {
	while(true) {
  		SDL_SetRenderDrawColor(gRenderer, 102, 94, 76, 0);
  		SDL_RenderClear(gRenderer);
  		SDL_Event sdlevent;
  		int SHUTDOWNCODE=0;
	    while (SDL_PollEvent(&sdlevent)) {
	        if (sdlevent.type==SDL_QUIT) {
	            SHUTDOWNCODE=1;
	            break;
	        }
			SDL_Event* e = &sdlevent;
			if(e->type != SDL_MOUSEMOTION && e->type != SDL_MOUSEBUTTONDOWN && e->type != SDL_MOUSEBUTTONUP) 
				continue;
			if(Inside_Box(e, 200, 300, 70, 30) == BUTTON_SPRITE_MOUSE_DOWN) {
				Save();
				return;
			}
			if(Inside_Box(e, 600, 300, 70, 30) == BUTTON_SPRITE_MOUSE_DOWN) {
				Load();
				return;
			}
	    }
	    if (SHUTDOWNCODE) break;
		boxRGBA(gRenderer, 200, 300, 270, 330, 0, 0, 0, 150);
		char ms[5] = "SAVE\0";
		SDL_Color color2 = { 255, 255, 255 };
		Print(ms, 200, 300, 10, 10, color2);
		boxRGBA(gRenderer, 600, 300, 670, 330, 0, 0, 0, 150);
		char ml[5] = "LOAD\0";
		SDL_Color color3 = { 255, 255, 255 };
		Print(ml, 600, 300, 10, 10, color3);
		SDL_RenderPresent(gRenderer);
  		SDL_Delay(1000/FPS);
  	}
}
