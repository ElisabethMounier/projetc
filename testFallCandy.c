#include "algo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main7() {

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


/*
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

    printf("\n Grid[4][7]=%d \n", temptGrid[4][7]);

*/
/*for (j=0; j<8; j++) {
  int x;
  int y;
    int avc=0;

    for (x=0; x<4; x++) {
      for (i=0; i<(4-avc); i++) {
        if (temptGrid[i+1][2]==0) {
        printf("Il y a une case vide");
        temptGrid[i+1][2]=temptGrid[i][2];
        temptGrid[i][2]=0;
        }
      }
      avc++;
    }
}*/


  int var=0;
  refreshTemptGrid();
  var=travelGrid();
  fallCandy();
  completeTemptGrid();
  refreshGrid();
  travelGrid();
  fallCandy();
  completeTemptGrid();
  refreshGrid();
  travelGrid();
  fallCandy();
  completeTemptGrid();
  refreshGrid();
  travelGrid();
  fallCandy();
  completeTemptGrid();
  refreshGrid();
  /*while (var!=0) {
    fallCandy();
    completeTemptGrid();
    refreshGrid();
    var=travelGrid();
     }*/







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
