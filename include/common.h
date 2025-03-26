#ifndef FINAL_COMMON_H
#define FINAL_COMMON_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<math.h>
#include<time.h>

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define HANDLE_ERROR(msg) printf(msg": %s\n", SDL_GetError());\
  exit(EXIT_FAILURE);

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool *keyboard;//存储所有按键按下状态
    //SDL_Surface *surface;//背景图
    SDL_Texture *texture;
    Mix_Music *bgm;//背景音乐
    TTF_Font *font;
    TTF_Font *score;
    TTF_Font *record;
    //SDL_Surface *surface_image;
    SDL_Texture *texture_image;
    //SDL_Surface *surface_square;
    SDL_Texture *texture_square;
    //SDL_Surface *surface_new_square;
    SDL_Texture *texture_new_square;
    Mix_Chunk *chunk1;
    Mix_Chunk *chunk2;
}App;

extern App app;
extern App page;

extern int score;
extern int record,record_rem;
extern char *Score;
extern char *Record;

#endif //FINAL_COMMON_H
