#include "algo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main4() {
    initGrid();
  initTemptGrid();

  printf("\n Affichage de Grid: \n");
  for (i=0; i<5; i++) {
    printf("\n");
    for (j=0; j<8; j++) {
      printf("%2d   ", grid[i][j]);
    }
  }

   printf("\n Affichage de temptGrid: \n");
  for (i=0; i<5; i++) {
    printf("\n");
    for (j=0; j<8; j++) {
      printf("%2d   ", temptGrid[i][j]);
    }
  }

printf("\n");
    int x1;
  int y1;
  printf("Entrer x1: ");
  scanf("%d", &x1);
  printf("Entrer y1: ");
  scanf("%d", &y1);

  int x2;
  int y2;
  printf("Entrer x2: ");
  scanf("%d", &x2);
  printf("Entrer y2: ");
  scanf("%d", &y2);

  move(x1, y1, x2, y2);




 printf("\n Affichage de Grid: \n");
  for (i=0; i<5; i++) {
    printf("\n");
    for (j=0; j<8; j++) {
      printf("%2d   ", grid[i][j]);
    }
  }


 printf("\n Affichage de temptGrid: \n");
  for (i=0; i<5; i++) {
    printf("\n");
    for (j=0; j<8; j++) {
      printf("%2d   ", temptGrid[i][j]);
    }
  }

return 1;



}
