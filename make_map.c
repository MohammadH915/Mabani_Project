#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
const int N = 1e3 + 100;
bool is[N][N];
bool hl[N][N];
char ch[8][2] = {"SH\0", "JW\0", "JS\0", "IL\0", "MS\0", "SG\0", "WG\0", "JB\0"};

int main() {
	FILE *fpout;
	fpout = fopen("jmap.txt", "w");
	if(fpout == NULL){
		printf("Cannot open\n");
		return -1;
	}
	printf("Lets Go to Make a Mr.Jack Map :) have fun ----- \n");
	printf("Inter width of Map\n");
	int width;
	scanf("%d", &width);
	printf("Inter hight of Map\n");
	int hight;
	scanf("%d", &hight);	
	fprintf(fpout, "%d %d\n", width, hight);
	printf("Be Careful !? : We assume the extra cells are also houses\n");
	printf("Inter number of houses In the map\n");
	int num_house;
	scanf("%d", &num_house);
	fprintf(fpout, "%d\n", num_house);
	printf("In %d line Inter two intiger x y such that x is less or equal to %d and y is less or equal to %d\n", num_house, width, hight);
	for(int i = 0; i < num_house; i++) {
		int x, y;
		while(true) {
			scanf("%d%d", &x, &y);
			if(is[x][y] == true) 
				printf("Input is not correct please Inter two integer that not occupied :( -Try again\n");
			else if(x > width)
				printf("x must be equal or less than %d ??? -Try again\n", width);
			else if (y > hight) 
				printf("y must be equal or less than %d !!! -Try again\n", hight);
			else {
				is[x][y] = true;
				break;
			}
		}
		fprintf(fpout, "%d %d\n", x, y);
	}
	printf("Inter number of Lights\n");
	int num_light;
	scanf("%d", &num_light);
	fprintf(fpout, "%d\n", num_light);
	printf("In %d line Inter three intiger x(hight of light), y(width of light), z(0 if light is off, 1 if on) such that x is less or equal to %d, y is less or equal to %d\n, z is 0 or 1\n", num_light, width, hight);
	for(int i = 0; i < num_light; i++) {
		int x, y, z;
		while(true) {
			scanf("%d%d%d", &x, &y, &z);
			if(is[x][y] == true) 
				printf("Input is not correct please Inter two integer that not occupied :( -Try again\n");
			else if(x > width)
				printf("x must be equal or less than %d ??? -Try again\n", width);
			else if (y > hight) 
				printf("y must be equal or less than %d !!! -Try again\n", hight);
			else if(z != 0 && z != 1)
				printf("z must be 0 or 1 !!! -Try again\n");
			else {
				is[x][y] = true;
				break;
			}
		}
		fprintf(fpout, "%d %d %d\n", x, y, z);
	}
	printf("Inter number of Holes\n");
	int num_holes;
	scanf("%d", &num_holes);
	fprintf(fpout, "%d\n", num_holes);
	printf("In %d line Inter three intiger x(hight of hole), y(width of hole), z(0 if hole is close, 1 if open) such that x is less or equal to %d, y is less or equal to %d\n, z is 0 or 1\n", num_holes, width, hight);
	for(int i = 0; i < num_holes; i++) {
		int x, y, z;
		while(true) {
			scanf("%d%d%d", &x, &y, &z);
			if(is[x][y] == true || hl[x][y] == true) 
				printf("Input is not correct please Inter two integer that not occupied :( -Try again\n");
			else if(x > width)
				printf("x must be equal or less than %d ??? -Try again\n", width);
			else if (y > hight) 
				printf("y must be equal or less than %d !!! -Try again\n", hight);
			else if(z != 0 && z != 1)
				printf("z must be 0 or 1 !!! -Try again\n");
			else {
				hl[x][y] = true;
				break;
			}
		}
		fprintf(fpout, "%d %d %d\n", x, y, z);
	}
	printf("In next 8 line Input 2 integer x(hight of charecter), y(width of charecter)\n");
	for(int i = 0; i < 8; i++) {
		printf("Specify %c%c's position\n", ch[i]);
		int x, y;
		while(true) {
			scanf("%d%d", &x, &y);
			if(is[x][y] == true) 
				printf("Input is not correct please Inter two integer that not occupied :( -Try again\n");
			else if(x > width)
				printf("x must be equal or less than %d ??? -Try again\n", width);
			else if (y > hight) 
				printf("y must be equal or less than %d !!! -Try again\n", hight);
			else {
				is[x][y] = true;
				break;
			}
		}
		fprintf(fpout, "%s\n", ch[i]);
		fprintf(fpout, "%d %d\n", x, y);
	}
	int ex;
	printf("Inter number of exits\n");
	scanf("%d", &ex);
	fprintf(fpout, "%d\n", ex);
	printf("In next %d line Input 3 integer x(hight of Exit), y(width of Exit), z (0 if close else 1)\n", ex);
	for(int i = 0; i < ex; i++) {
		int x, y, z;
		while(true) {
			scanf("%d%d%d", &x, &y, &z);
			if(is[x][y] == true) 
				printf("Input is not correct please Inter two integer that not occupied :( -Try again\n");
			else if(x > width)
				printf("x must be equal or less than %d ??? -Try again\n", width);
			else if (y > hight) 
				printf("y must be equal or less than %d !!! -Try again\n", hight);
			else {
				is[x][y] = true;
				break;
			}
		}
		fprintf(fpout, "%d %d %d\n", x, y, z);
	}

	fclose(fpout);
	return 0;
}
