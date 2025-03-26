#include<main.h>

App app;
App page;

int main(int argc, char *argv[]){
    init_app();

    startup();//启动界面

    do_game();

    atexit(&quit_app);

    return 0;
}

static void init_app(){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        HANDLE_ERROR("Init SDL");
    }
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        HANDLE_ERROR("Init Image");
    }
    if(!Mix_Init(MIX_INIT_OGG)){
        HANDLE_ERROR("Init Mixer");
    }
    if(TTF_Init() == -1){
        HANDLE_ERROR("Init TTF");
    }
    //创建窗口
    app.window = SDL_CreateWindow("TakeAJump", 200, 100, 360, 640, SDL_WINDOW_SHOWN);
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);

    Score = calloc(1000,sizeof(char));
    Record = calloc(1000,sizeof(char));
}

static void quit_app(){
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();

    free(Score);
    free(Record);

    printf("End up!\n");

    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
}