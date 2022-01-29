jackmap: 
	gcc make_map.c -o map_game -I include -L lib -l SDL2-2.0.0 -L lib -l SDL2_gfx-1.0.0 
game:
	gcc main.c -o play -I include -L lib -l SDL2-2.0.0 -L lib -l SDL2_gfx-1.0.0 -L lib -l SDL2_image-2.0.0 -L lib -l SDL2_ttf-2.0.0
