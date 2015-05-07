#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct candy candy ;
struct candy
{
	int n;
};


const int YELLOW = 1 ;
const int PURPLE = 2 ;
const int ORANGE = 3 ;
const int GREEN = 4 ;
const int BLUE = 5 ;
const int RED = 6 ;


typedef struct grid grid ;
struct grid
{
	int tab[8][5];
	int score;
	int level;
};

int main(){
	srand(time(NULL));
	grid grille;	
	fill(&grille);
	int i,j;
	 // initialisation de rand pour remplir le tableau
	for (i=0; i<7; i++) {
		for (j=0; j<5; j++) {
			printf("%d\n", grille.tab[i][j]);
		}
	}
	return 0;
}


void fill(grid* grille) {
	int i,j;
	for (i=0; i<7; i++) {
		for (j=0; j<4; j++) {
			grille->tab[i][j]=rand()%(6) +1 ;
		}
	}
}


void switch_candies(int x1, int y1, int x2, int y2, grid* grille) {
	if (test_can_switch(x1,x2,y1,y2)) {
		int aux = grille->tab[x2][y2] ;
		grille->tab[x2][y2] = grille->tab[x1][y1] ;
		grille->tab[x1][y1] = aux ;
	}
}


int test_alignment(grid* grille) {
	int i,j;	
	for (i=0; i<7; i++) {
		for (j=0; j<4; j++) {
			if (grille->tab[i][j]==grille->tab[i-1][j] && grille->tab[i][j]==grille->tab[i+1][j] || grille->tab[i][j]==grille->tab[i-1][j] && grille->tab[i][j]==grille->tab[i-2][j] || grille->tab[i][j]==grille->tab[i+1][j] && grille->tab[i][j]==grille->tab[i+2][j]) {
				return 1 ;
			}
			else if (grille->tab[i][j]==grille->tab[i][j-1] && grille->tab[i][j]==grille->tab[i][j+1] || grille->tab[i][j]==grille->tab[i][j-1] && grille->tab[i][j]==grille->tab[i][j-2] || grille->tab[i][j]==grille->tab[i][j+1] && grille->tab[i][j]==grille->tab[i][j+2]) {
				return 1 ;
			}
			else {
				return 0 ;
			}
		}
	}
}


int test_can_switch(int x1, int x2, int y1, int y2, grid* grille) {
	if(y1==y2 && x1==x2+1 || y1==y2 && x1==x2-1) {
		if ((grille->tab[x1][y1]==grille->tab[x2][y2+1] && grille->tab[x1][y1]==grille->tab[x2][y2+2]) || (grille->tab[x1][y1]==grille->tab[x2][y2-1] && grille->tab[x1][y1]==grille->tab[x2][y2+1]) || (grille->tab[x1][y1]==grille->tab[x2][y2-1] && grille->tab[x1][y1]==grille->tab[x2][y2-2])) {
			return 1 ;
		}
		else {
			return 0 ;
		}
	}
	else if (x1==x2 && y1==y2+1 || x1==x2 && y1==y2-1) {
		if (grille->tab[x1][y1]==grille->tab[x2+1][y2] && grille->tab[x1][y1]==grille->tab[x2+2][y2] || grille->tab[x1][y1]==grille->tab[x2-1][y2] && grille->tab[x1][y1]==grille->tab[x2+1][y2] || grille->tab[x1][y1]==grille->tab[x2-1][y2] && grille->tab[x1][y1]==grille->tab[x2-2][y2]) {
			return 1 ;
		}
		else {
			return 0 ;
		}
	}
	else {
		return 0 ;
	}
}






	
	



