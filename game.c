#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //pour l'initialisation de rand


/***********************************/
/*           1.CONSTANTES          */
/***********************************/

int tempt_grid[5][8];      //grille de suppresion des bonbons, elle n'est pas affich�e 
int grid[5][8];            //grille d'affichage
int i;                     //pour parcourir les lignes (boucles for)
int j;                     //pour parcourir les colonnes (boucles for)
int score;                 //score calculer lignes par lignes et colonnes par colonnes, utiliser dans travelLine() et travelColumn()
int moves=0;               //nombre de d�placements de bonbons
int total_score;           //score total 
int couch;                 //les couches permettent de calculer le score


/***************************************************************/
/*           2.FONCTIONS SUR LES GRILLES                       */
/***************************************************************/

//initialisation de Grid de mani�re al�atoire, la grille affich�e
void init_grid() {
  // initialisation de rand 
  srand(time(NULL)); 
  for (i=0; i<5; i++) {
    for (j=0; j<8; j++) {
      grid[i][j]=rand()%6+1;
    }
  }
}

//initialisation de tempt_grid � zero, la grille temporaire 
void init_tempt_grid() {
  for (i=0; i<5; i++) {
    for (j=0; j<8; j++) {
      tempt_grid[i][j]=0;
    }
  }
}

//grid=tempt_grid
void refresh_grid() {
  int i;
  int j;

  for (i=0; i<5; i++) {
    for (j=0; j<8; j++) {
      grid[i][j]=tempt_grid[i][j];
    }
  }
}

//tempt_grid=grid
void refresh_tempt_grid() {
  int i;
  int j;

  for (i=0; i<5; i++) {
    for (j=0; j<8; j++) {
      tempt_grid[i][j]=grid[i][j];
    }
  }
}


//echange 2 bonbons dans grid
void switch_candy(int x1, int y1, int x2, int y2) {
  int var;
  //variable pour sauvegarder la valeur de grid[x1][y1]  
  var=grid[x1][y1]; 
  grid[x1][y1]=grid[x2][y2];
  grid[x2][y2]=var;
}



//fais monter les 0 dans les colonnes
//Les zeros correspond � "case vide", c'est comme-ci on faisait "tomber les bonbons dans la grille"
void fall_candy() {
  for (j=0; j<8; j++) {
    int x;
    //avancement, pour optimiser le nombre de parcours de la colonne    
    int avc=0; 

    for (x=0; x<4; x++) {
      for (i=0; i<(4-avc); i++) {
        if (tempt_grid[i+1][2]==0) {
	  printf("Il y a une case vide");
	  tempt_grid[i+1][2]=tempt_grid[i][2];
	  tempt_grid[i][2]=0;
        }
      }
      avc++;
    }
  }

}


//genere al�atoirement un chiffre entre 1 et 6 (=bonbon) l� o� il y a des zeros (=case vide)
void complete_tempt_grid() { 
  for (j=0; j<8; j++) {
    for (i=0; i<5; i++) {
      if (tempt_grid[i][j]==0) {
	tempt_grid[i][j]=rand()%6+1;
	printf("On rempli une case vide");
      }
    }
  }
}


/*******************************************************************/
/*           3.FONCTIONS D'ANALYSE DES LIGNES ET COLONNES          */
/*******************************************************************/


//simple fonction qui compare dans Grid 2 bonbons sur une ligne
int compare_line(int i, int j) {
  if (grid[i][j]==grid[i][j+1]) {
    return 1;
  }
  else {return 0;}
}


//simple fonction qui compare dans Grid 2 bonbons sur une colonne
int compare_column(int i, int j) {
  if (grid[i][j]==grid[i+1][j]) {
    return 1;
  }
  else {return 0;}
}


//fonction qui parcours la ligne i dans grid, 
//met � zero les bonbons � exploser dans tempt_grid,
// attribue le score en fonction des couches
void travel_line(int i) {

  int cpt=0;           //compteur, compte le nombre de bonbon align�
  for (j=0; j<7; j++) {

    //CAS 1: 2 bonbons align�s et on est pas � la fin de la ligne
    if (compare_line(i,j)==1 && j!=6) {
      printf("%d identiques\n", cpt+2);
      //on incr�ment cpt, car 1 bonbon de plus align�
      cpt++;
    }

    //CAS 2: 2 bonbons align�s, on est � la fin de la ligne et avant il y a plus de 2 bonbons align�s
    else if (compare_line(i,j)==1 && j==6 && cpt>0) {
      printf("%d identiques et fin de lignes on met a zero les identiques\n", cpt+2);
      int x;
      //on incr�ment cpt, car 1 bonbon de plus align�
      cpt++;
      for (x=0; x<cpt+1; x++) {
	//on met � zero les bonbons align�s (minimum 3) en utilisant cpt
	tempt_grid[i][j+1-x]=0;
      }
      //gestion du score pour la ligne
      score=score+(cpt-1)*60*(couch+1); //le score est plus important quand les bonbons sont cass�s dans une couche sup�rieur
      cpt=0;
    }

    //CAS 3: 2 bonbons align�, fin de ligne et moins de 3 bonbons align�s
    else if (compare_line(i,j)==1 && j==6 && cpt<1) {
      printf("identiques et fin de ligne et rien a supp avant\n");
      cpt=0;
    }

    //CAS 4: 2 bonbons diff�rents et plus de 2 bonbons align�s avant
    else if (compare_line(i,j)==0 && cpt>1) {
      printf("differents et on supprime les identiques avant\n");
      int x;
      for (x=0; x<cpt+1; x++) {
	tempt_grid[i][j-x]=0;
      }
      score=score+(cpt-1)*60*(couch+1);
      cpt=0;
    }

    //CAS 5: 2 bonbons diff�rents et moins de 3 bonbons align�s avant
    else if (compare_line(i,j)==0 && cpt<2) {
      printf("diff et rien a supp avant\n");
      cpt=0;
    }
    
    //CAS de d�tection d'erreurs, jamais rencontr�
    else {
      printf("Erreur: pas de cas pr�vu.");
    }

  }
}


//fonction qui parcours la colonne j dans grid, 
//met � zero les bonbons � exploser dans tempt_grid,
// attribue le score en fonction des couches
//(voir les commentaires dans travel_line(int i))
void travel_column(int j) {

  int cpt=0;
  for (i=0; i<4; i++) {

    if (compare_column(i,j)==1 && i!=3) {
      printf("%d identiques\n", cpt+2);
      cpt++;
    }

    else if (compare_column(i,j)==1 && i==3 && cpt<1) {
      printf("identiques et fin de colonne et rien a supp avant\n");
      cpt=0;
    }

    else if (compare_column(i,j)==1 && i==3 && cpt>0) {
      printf("%d identiques et fin de colonne on met a zero\n", cpt+2);
      int x;
      cpt++;
      for (x=0; x<cpt+1; x++) {
	tempt_grid[i+1-x][j]=0;
      }
      score=score+(cpt-1)*60*(couch+1);
      cpt=0;
    }

    else if (compare_column(i,j)==0 && cpt>1) {
      printf("differents et on supprime les identiques avant\n");
      int x;
      for (x=0; x<cpt+1; x++) {
	tempt_grid[i-x][j]=0;
      }
      score=score+(cpt-1)*60*(couch+1);
      cpt=0;
    }

    else if (compare_column(i,j)==0 && cpt<2) {
      printf("diff et rien a supp avant\n");
      cpt=0;
    }

    else {
      printf("Erreur: pas de cas pr�vu.");
    }

  }
}


/*******************************************************************/
/*           4.FONCTIONS D'ANALYSE DE LA GRILLE                    */
/*******************************************************************/

//fonction qui parcourt toute la grille, colonne par colonne et ligne par ligne
//elle retourn le score calculer pour ce parcourt
int travel_grid() {

  score=0;
  for (i=0; i<5; i++) {
    travel_line(i);
  }
  for (j=0; j<8; j++) {
    travel_column(j);
  }
  return score;
}


//fonction qui gere la selection de 2 bonbons de Grid r�p�r� par leurs "coordonn�es" pour les d�placer
void move(int x1, int y1, int x2, int y2) { 

  //initialisation des couches
  couch=0;

  //CAS 1: les bonbons ne sont pas � cot�, on ne change rien
  if ((x1==x2 && abs(y1-y2)!=1) || (y1==y2 && abs(x1-x2)!=1) || (x1!=x2 && y1!=y2)) {
    printf("On ne change rien, les bonbons ne sont pas a cote");
  }

  //CAS 2: les bonbons sont identiques, on ne change rien
  if (grid[x1][y1]==grid[x2][y2]) {
    printf("On ne change rien, les bonbons sont identiques");
  }
  
  //CAS 3: les bonbons sont diff�rents et � cot�
  else {
    switch_candy(x1,y1,x2,y2);
    refresh_tempt_grid();
    //on parcourt la grille et on retient le score dans var
    int var=travel_grid(); 

    //CAS 3.1: pas de bonbons � exploser (ie score r�alis� par travel_grid)
    if (var==0) {
      //On remet les bonbons en place
      switch_candy(x1,y1,x2,y2);
      printf("Deplacement pas possible, pas de bonbons a detruire");
    }
    
    //CAS 3.2: il y a des bonbons qui ont explos�s
    else if (var>=0) {
      //on incr�ment le nombre de d�placement
      moves++;
      //on ajoute le score r�alis� par ce parcourt de grid
      total_score=total_score+var;

      while (var!=0) {
	//on passe � une autre couche
	couch++;
	total_score=total_score+var;
	fall_candy();
	complete_tempt_grid();
	//le joueur voit d�sormais l'effet de son d�placement !
	refresh_grid();
	//on reparcourt la grille pour voir si d'autres bonbons sont � d�truire
	var=travel_grid();
      }
    }
  }
}


//fonction qui, � l'initialisation, cr�e une grille sans plus de 2 bonbons align�s
void create_a_good_grid() {
  int var=0;
  refresh_tempt_grid();
  var=travel_grid();
  while (var!=0) {
    fall_candy();
    complete_tempt_grid();
    refresh_grid();
    var=travel_grid();
  }
}


