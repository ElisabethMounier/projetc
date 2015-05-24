#include "algo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main5() {
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

 refreshTemptGrid();

  printf("\n Affichage de temptGrid: \n");
  for (i=0; i<5; i++) {
    printf("\n");
    for (j=0; j<8; j++) {
      printf("%2d   ", temptGrid[i][j]);
    }
  }




switchCandy(0,4,0,5);




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
