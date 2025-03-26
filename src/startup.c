#include<startup.h>

void startup(){
    printf("Startup!\n");
    SDL_Event start;

    //显示第一张背景图
    //page.surface = IMG_Load(".\\res\\pictures\\startup.jpg");
    //page.texture = SDL_CreateTextureFromSurface(app.renderer, page.surface);
    page.texture = IMG_LoadTexture(app.renderer, ".\\res\\pictures\\startup.jpg");
    SDL_RenderCopy(app.renderer, page.texture, NULL, NULL);

    //显示提示
    page.font = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",20);
    SDL_Color color_hint = {0x3f, 0x5f, 0x4f ,0xff};
    SDL_Surface *surface_hint = TTF_RenderText_Blended_Wrapped(page.font, "Press your keyboard to access the game or press Escape to exit.",color_hint,300);
    SDL_Texture *texture_hint = SDL_CreateTextureFromSurface(app.renderer, surface_hint);
    SDL_Rect rect_hint = {.x = 30, .y = 540};
    SDL_QueryTexture(texture_hint, NULL, NULL, &rect_hint.w, &rect_hint.h);
    SDL_RenderCopy(app.renderer, texture_hint,NULL, &rect_hint);

    SDL_Surface *surface_name = TTF_RenderText_Blended(page.font, "Created by Luemo.",color_hint);
    SDL_Texture *texture_name = SDL_CreateTextureFromSurface(app.renderer, surface_name);
    SDL_Rect rect_name = {.x = 100, .y = 200};
    SDL_QueryTexture(texture_name, NULL, NULL, &rect_name.w, &rect_name.h);
    SDL_RenderCopy(app.renderer, texture_name, NULL, &rect_name);
    SDL_RenderPresent(app.renderer);

    //配置音频信息
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    page.bgm = Mix_LoadMUS(".\\res\\music\\first_bgm.ogg");

    printf("Play Startup Music!\n");
    Mix_PlayMusic(page.bgm, -1);
    while(SDL_WaitEvent(&start)){
        if(start.type == SDL_QUIT){
            Mix_HaltMusic();
            printf("Quit by SDL_QUIT!\n");
            SDL_Quit();
            exit(0);
        }
        else if(start.type == SDL_KEYDOWN && start.key.keysym.sym != SDLK_ESCAPE){
            Mix_HaltMusic();
            break;
        }
        else if(start.type == SDL_KEYDOWN && start.key.keysym.sym == SDLK_ESCAPE){
            Mix_HaltMusic();
            printf("Quit by ESC!\n");
            SDL_Quit();
            exit(0);
        }
    }

    //关闭背景
    SDL_DestroyTexture(page.texture);
    //SDL_FreeSurface(page.surface);

    //关闭提示
    SDL_DestroyTexture(texture_hint);
    SDL_FreeSurface(surface_hint);

    SDL_DestroyTexture(texture_name);
    SDL_FreeSurface(surface_name);

    TTF_CloseFont(page.font);

    //关闭音频
    Mix_FreeMusic(page.bgm);
    Mix_CloseAudio();
}

