#ifndef game_h
#define game_h

int tempt_grid[5][8];
int grid[5][8];
int x11, x22, y11, y22;
int i;
int j;
int score;
int moves;
int rest_moves;
int target;
int total_score;
int couch;
void init_grid();
void init_tempt_grid();
void refresh_grid();
void refresh_tempt_grid();
void switch_candy();
void fall_candy();
void complete_tempt_grid();
int compare_line(int i, int j);
int compare_column(int i, int j);
void travel_line(int i);
void travel_column(int j);
int travel_grid();
void move(int, int, int, int);
void create_a_good_grid();
void play_level_1();
void play_level_1_terminal();
void play_level_1();


#endif
