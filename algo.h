#ifndef algo_h
#define algo_h


int temptGrid[5][8];
int grid[5][8];
int i;
int j;
int score;
int totalscore;
int zero[8];
void initGrid(); //genere une grille aleatoire de 6 bonbons
void initTemptGrid(); // genere la grille a 0
int compareLine(int i, int j); //compare 2 bonbons sur la meme ligne
int travelLine(int i); //regarde Grid et met a 0 les chaines de plus de 3 bonbons dans temptGrid
void refreshGrid(); //grid=temptGrid;
void refreshTemptGrid(); //temptGrid=grid
void compareColumn();
void travelColumn();
int travelGrid(); //parcourt toute la Grid avec les fonctions travelLine et travelColumn
void switchCandy(int x1, int y1, int x2, int y2); //echange 2 bonbons dans Grid reperes par leurs coordonnees dans la grid
void fallCandy(); //fait tomber les bonbons dans la grille (ie remonter les zeros);
void completeGrid(); //genere des bonbons la ou ya des zeros
void strok(int x1, int y1, int x2, int y2); //gere tout quand on selectione 2 bonbons
void createAGoodGrid();

#endif
