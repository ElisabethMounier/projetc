#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//dans lalgo on mets bien les zero dans la grille daffichage mais ET on switch les 2 bonbons, si score =0 on reswitch les bonbons

//fonction refresh Grid


int temptGrid[5][8];
int grid[5][8];
int i;
int j;
int score;
int totalscore;
int zero[8];

void initGrid() {
  for (i=0; i<5; i++) {
    for (j=0; j<8; j++) {
      grid[i][j]=rand()%6+1;
    }
  }
}

void initTemptGrid() {
  for (i=0; i<5; i++) {
    for (j=0; j<8; j++) {
      temptGrid[i][j]=0;
    }
  }
}


int compareLine(int i, int j) {
  if (grid[i][j]==grid[i][j+1]) {
    return 1;
  }
  else {return 0;}
}

void travelLine(int i) {

  int cpt=0;
  for (j=0; j<7; j++) {

    if (compareLine(i,j)==1 && j!=6) {
      printf("%d identiques\n", cpt+2);
      cpt++;
    }
    else if (compareLine(i,j)==1 && j==6 && cpt>1) {
      printf("%d identiques et fin de lignes on met a zero les identiques\n", cpt+2);
      int x;
      cpt++;
      for (x=0; x<cpt+1; x++) {
    temptGrid[i][j+1-x]=0;

      }
      score=score+(cpt-1)*60;
      cpt=0;
    }
     else if (compareLine(i,j)==1 && j==6 && cpt<2) {
      printf("identiques et fin de ligne et rien a supp avant\n");
      cpt=0;
    }

    else if (compareLine(i,j)==0 && cpt>1) {
      printf("differents et on supprime les identiques avant\n");
      int x;
      for (x=0; x<cpt+1; x++) {
    temptGrid[i][j-x]=0;
      }
      score=score+(cpt-1)*60;
      cpt=0;
    }
    else if (compareLine(i,j)==0 && cpt<2) {
      printf("diff et rien a supp avant\n");
      cpt=0;
    }

  }
}

int compareColumn(int i, int j) {
  if (grid[i][j]==grid[i+1][j]) {
    return 1;
  }
  else {return 0;}
}

void travelColumn(int j) {

  int cpt=0;
  for (i=0; i<4; i++) {

    if (compareColumn(i,j)==1 && i!=3) {
      printf("%d identiques\n", cpt+2);
      cpt++;
    }
     else if (compareColumn(i,j)==1 && i==3 && cpt<1) {
      printf("identiques et fin de colonne et rien a supp avant\n");
      cpt=0;
    }
    else if (compareColumn(i,j)==1 && i==3 && cpt>0) {
      printf("%d identiques et fin de colonne on met a zero\n", cpt+2);
      int x;
      cpt++;
      for (x=0; x<cpt+1; x++) {
            temptGrid[i+1-x][j]=0;

      }
      score=score+(cpt-1)*60;
      cpt=0;
    }
    else if (compareColumn(i,j)==0 && cpt>1) {
      printf("differents et on supprime les identiques avant\n");
      int x;
      for (x=0; x<cpt+1; x++) {
    temptGrid[i-x][j]=0;
      }
      score=score+(cpt-1)*60;
      cpt=0;
    }
    else if (compareColumn(i,j)==0 && cpt<2) {
      printf("diff et rien a supp avant\n");
      cpt=0;
    }

  }
}

void refreshGrid() {
  int i;
  int j;

  for (i=0; i<5; i++) {
    for (j=0; j<8; j++) {
      grid[i][j]=temptGrid[i][j];
    }
  }
}

void refreshTemptGrid() {
  int i;
  int j;

  for (i=0; i<5; i++) {
    for (j=0; j<8; j++) {
      temptGrid[i][j]=grid[i][j];
    }
  }
}

int travelGrid() { //il faut parcourir la grille affichee! pas temptGrid et on modifie bien la temptGrid
  score=0;
  for (i=0; i<5; i++) {
    travelLine(i);
  }
  for (j=0; j<8; j++) {
    travelColumn(j);
  }
  return score;
}

void switchCandy(int x1, int y1, int x2, int y2) {
  int var;
  var=grid[x1][y1];
  grid[x1][y1]=grid[x2][y2];
  grid[x2][y2]=var;
}



void fallCandy() {
  int x;
  int avc=0; //avancement
  for (x=0; x<4; x++) {
    for (j=0; j<8; j++) {
      for (i=1; i<5-avc; i++) {
    if (temptGrid[i][j]==0) {
      printf("Il y a une case vide");
      temptGrid[i][j]=temptGrid[i-1][j];
      temptGrid[i-1][j]=0;
    }
      }
    }
    avc++;
  }
}



void completeGrid() { //genere de nouveaux bonbons dans les cases vides
  for (j=0; j<8; j++) {
    for (i=0; i<5; i++) {
      if (temptGrid[i][j]==0) {
    temptGrid[i][j]=rand()%6+1;
    printf("On rempli une case vide");
      }
    }
  }
}

void strok(int x1, int y1, int x2, int y2) { //prevoir un compteur qui compte le nombre de strock car celui ci est limité


  if (grid[x1][y1]==grid[x2][y2]) {
    printf("On ne change rien, les bonbons sont identiques");
  }
  else {
    switchCandy(x1,y1,x2,y2);
    int var2=travelGrid(); //on parcourt la grille

    if (var2==0) {
      switchCandy(x1,y1,x2,y2);
      printf("Deplacement pas possible, pas de bonbons a detruire");
      //incrementer le compteur de strock de 1

    }
    else if (var2>=0) {
      //totalScore=totalScore+score;
      while (var2!=0) {
    refreshTemptGrid();
    fallCandy();
    completeGrid();
    refreshGrid();
    var2=travelGrid();
      }
    }
  }
}



void createAGoodGrid() {
  int var=0;
  var=travelGrid();
  while(var!=0) {
    refreshTemptGrid();
    fallCandy();
    completeGrid();
    refreshGrid();
  }


}
