#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algo.h"

//int target;   //objectif=score � atteindre pour gagner la partie
int free_moves;
//int rest_moves;


//fontion qui g�re le niveau 1
void initialize_level_1() {

  //initialisation du score totale
  total_score=0;
  //fixation de l'objectif
  target=1500;
  //fixation du nombre de d�placement autoris�
  free_moves=10;

  moves=0;
  //initialisation du nombre de d�placement restant
  rest_moves=free_moves;
  //initialisation des grilles
  init_grid();
  init_tempt_grid();
  create_a_good_grid();


}
  //gestion de la partie
  //while(rest_moves!=0) { comme tu remarque j'enleve le while(rest_moves!=0) il faudra donc le mettre avec le main directement

void play(int x1, int y1, int x2, int y2) { //l'idee c'est que suivant la ou on clique dans la grille on assigne � x1 x2 y1 y2 des valeurs
    //et on appelle cette fonction
   //Sarah Je pense que c'est l� que �a doit beuger, et c'est bien level que tu dois utiliser mais pas strock directement,
   //apr�s il faut l'ajouter au main, il faurdait que tu commit ce que tas fait la semaine derniere pour que je vois ou
   //ca peut poser probleme, j'ai fait des changements plus haut pour essayer de taider � gerer �a avec la sdl

    //int x1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!A g�rer avec la sdl, donner la valeur en fonction du bonbon s�l�ctionner
    //attention, x1 correspond � mes i et y1 � mes j
    //int y1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!A g�rer avec la sdl
    //int x2; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!A g�rer avec la sdl
    //int y2; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!A g�rer avec la sdl


    move(x1, y1, x2, y2);
    printf("Nombre de couche: %d", couch);
    rest_moves=free_moves-moves;
    printf("\n Il te reste: %d\n deplacement", rest_moves);
    printf("\n Ton score: %d\n", total_score);
  //}

  //gestion de fin de la partie: gagn� ou perdu
/*  if (total_score<target) {
    printf("Dommage ! Tu n'a pas atteint l'objectif..");
  }
  else {
    printf("Bravo! Tu as gagne");
  }*/

}


