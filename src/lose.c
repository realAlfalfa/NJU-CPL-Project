#include<lose.h>

char *Score;
char *Record;

void Lose(){
    printf("Lose!\n");
    //游戏背景图
    //page.surface = IMG_Load();
    //page.texture = SDL_CreateTextureFromSurface(app.renderer, page.surface);
    page.texture = IMG_LoadTexture(app.renderer, ".\\res\\pictures\\lose.jpg");
    SDL_RenderCopy(app.renderer, page.texture, NULL, NULL);

    //配置音频信息
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    page.bgm = Mix_LoadMUS(".\\res\\music\\lose.ogg");

    printf("Play Lose Music!\n");
    Mix_PlayMusic(page.bgm, -1);

    //显示提示
    page.font = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",20);
    SDL_Color color_hint = {0x3f, 0x5f, 0x4f ,0xff};
    SDL_Surface *surface_hint = TTF_RenderText_Blended_Wrapped(page.font, "Press your keyboard to try again or press Escape to exit.",color_hint,300);
    SDL_Texture *texture_hint = SDL_CreateTextureFromSurface(app.renderer, surface_hint);
    SDL_Rect rect_hint = {.x = 30, .y = 510};
    SDL_QueryTexture(texture_hint, NULL, NULL, &rect_hint.w, &rect_hint.h);
    SDL_RenderCopy(app.renderer, texture_hint,NULL, &rect_hint);

    //显示得分
    page.score = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",28);
    SDL_Color color_score = {0x3f, 0x5f, 0x4f ,0xff};
    SDL_Surface *surface_score = TTF_RenderText_Blended(page.score, Score,color_score);
    SDL_Texture *texture_score = SDL_CreateTextureFromSurface(app.renderer, surface_score);
    SDL_Rect rect_score = {.x = 200, .y = 135};
    SDL_QueryTexture(texture_score, NULL, NULL, &rect_score.w, &rect_score.h);
    SDL_RenderCopy(app.renderer, texture_score,NULL, &rect_score);

    page.record = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",28);
    SDL_Color color_record = {0x3f, 0x5f, 0x4f ,0xff};
    SDL_Surface *surface_record = TTF_RenderText_Blended(page.record, Record,color_record);
    SDL_Texture *texture_record = SDL_CreateTextureFromSurface(app.renderer, surface_record);
    SDL_Rect rect_record = {.x = 200, .y = 180};
    SDL_QueryTexture(texture_record, NULL, NULL, &rect_record.w, &rect_record.h);
    SDL_RenderCopy(app.renderer, texture_record,NULL, &rect_record);

    SDL_RenderPresent(app.renderer);

    SDL_Event lose;
    while(SDL_WaitEvent(&lose)){
        if(lose.type == SDL_QUIT){
            printf("Quit by SDL_QUIT!\n");
            //关闭背景
            //SDL_FreeSurface(page.surface);
            SDL_DestroyTexture(page.texture);

            //关闭文字
            SDL_FreeSurface(surface_hint);
            SDL_DestroyTexture(texture_hint);

            SDL_FreeSurface(surface_record);
            SDL_DestroyTexture(texture_record);

            SDL_FreeSurface(surface_score);
            SDL_DestroyTexture(texture_score);

            TTF_CloseFont(page.font);
            TTF_CloseFont(page.score);
            TTF_CloseFont(page.record);

            //关闭音频
            Mix_FreeMusic(page.bgm);
            Mix_CloseAudio();
            //SDL_Quit();
            exit(0);
        }
        else if(lose.type == SDL_KEYDOWN){
            Mix_HaltMusic();
            //关闭背景
            //SDL_FreeSurface(page.surface);
            SDL_DestroyTexture(page.texture);

            //关闭文字
            SDL_FreeSurface(surface_hint);
            SDL_DestroyTexture(texture_hint);

            SDL_FreeSurface(surface_record);
            SDL_DestroyTexture(texture_record);

            SDL_FreeSurface(surface_score);
            SDL_DestroyTexture(texture_score);

            TTF_CloseFont(page.font);
            TTF_CloseFont(page.score);
            TTF_CloseFont(page.record);

            //关闭音频
            Mix_FreeMusic(page.bgm);
            Mix_CloseAudio();
            if(lose.key.keysym.sym != SDLK_ESCAPE)
                do_game();
            else
                exit(0);
            break;
        }
    }
}




