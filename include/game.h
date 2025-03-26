//
// Created by Luemo on 2024/1/11.
//

#ifndef FINAL_GAME_H
#define FINAL_GAME_H

#include<common.h>

#define SCORE_X 160
#define SCORE_Y 55

#define RECORD_X 160
#define RECORD_Y 6

#define W 140
#define H 130

int newX,newY;
int loc_square_x, loc_square_y;
char *square_rem,*square_remember;
char *image_rem;

int GetNum(int i);

void do_game();

void take_a_jump(unsigned int time, int X, int Y);
void draw_render();

void draw_square();
void draw_dog();

bool is_centered();

void back();

void break_the_record();
void Lose();

void new_square();

void draw_score(int x, int y);
void draw_record(int x,int y);

#endif //FINAL_GAME_H
