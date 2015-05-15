#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int target;   //objectif=score à atteindre pour gagner la partie
int free_moves;
int rest_moves;


//fontion qui gère le niveau 1
void play_level_1_terminal() {

  //initialisation du score totale
  total_score=0;
  //fixation de l'objectif
  target=3000;
  //fixation du nombre de déplacement autorisé
  free_moves=5;
  //initialisation du nombre de déplacement restant
  rest_moves=free_moves;
  //initialisation des grilles
  init_grid();
  init_tempt_grid();
  create_a_good_grid();


  //gestion de la partie
  while(rest_moves!=0) {

    //affichage de la grille pour jouer dans le terminal
    for (i=0; i<5; i++) {
      printf("\n");
      for (j=0; j<8; j++) {
	printf("%2d   ", grid[i][j]);
      }
    }
    printf("\n A toi de jouer: \n");

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
    printf("Nombre de couche: %d", couch);
    rest_moves=free_moves-moves;
    printf("\n Il te reste: %d\n deplacement", rest_moves);
    printf("\n Ton score: %d\n", total_score);
  }

  //gestion de fin de la partie: gagné ou perdu
  if (total_score<target) {
    printf("Dommage ! Tu n'a pas atteint l'objectif..");
  }
  else {
    printf("Bravo! Tu as gagne");
  }

}


