#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main2() {
  initGrid();
  initTemptGrid();

  grid[4][0]=0;


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

  createAGoodGrid();



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
  return 1;
}
