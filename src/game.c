#include<game.h>

int score, cnt;
int record,record_rem;
char *Score;
char *Record;

char *Point[23] = {
        ".\\res\\pictures\\square1.png",
        ".\\res\\pictures\\square2.png",
        ".\\res\\pictures\\square3.png",
        ".\\res\\pictures\\square4.png",
        ".\\res\\pictures\\square5.png",
        ".\\res\\pictures\\square6.png",
        ".\\res\\pictures\\square7.png",
        ".\\res\\pictures\\square8.png",
        ".\\res\\pictures\\square9.png",
        ".\\res\\pictures\\square10.png",
        ".\\res\\pictures\\square11.png",
        ".\\res\\pictures\\square12.png",
        ".\\res\\pictures\\square13.png",
        ".\\res\\pictures\\square14.png",
        ".\\res\\pictures\\square15.png",
        ".\\res\\pictures\\square16.png",
        ".\\res\\pictures\\square17.png",
        ".\\res\\pictures\\square18.png",
        ".\\res\\pictures\\square19.png",
        ".\\res\\pictures\\square20.png",
        ".\\res\\pictures\\square21.png",
        ".\\res\\pictures\\square22.png",
        ".\\res\\pictures\\square23.png"
};

char *Point2[2] = {
        ".\\res\\pictures\\line_puppy2.png",
        ".\\res\\pictures\\line_puppy3.png"
};

char *Point3[3] = {
        ".\\res\\music\\surprise1.ogg",
        ".\\res\\music\\surprise2.ogg",
        ".\\res\\music\\surprise3.ogg"
};

void do_game(){
    score = 0, cnt = 0;
    printf("Opening game!\n");
    SDL_Event game;

    draw_render();

    //游戏提示
    page.font = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",20);
    SDL_Color color_hint = {0x3f, 0x5f, 0x4f ,0xff};
    SDL_Surface *surface_hint = TTF_RenderText_Blended_Wrapped(page.font, "Line puppy wants to go out.\n\nPress your mouse button to help him!\n\nWish you a good score!",color_hint,300);
    SDL_Texture *texture_hint = SDL_CreateTextureFromSurface(app.renderer, surface_hint);
    SDL_Rect rect_name = {.x = 40, .y = 110};
    SDL_QueryTexture(texture_hint, NULL, NULL, &rect_name.w, &rect_name.h);
    SDL_RenderCopy(app.renderer, texture_hint,NULL, &rect_name);

    //得分
    page.score = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",28);
    SDL_Color color_score = {0x3f, 0x5f, 0x4f ,0xff};
    SDL_Surface *surface_score = TTF_RenderText_Blended(page.score, Score,color_score);
    SDL_Texture *texture_score = SDL_CreateTextureFromSurface(app.renderer, surface_score);

    //记录
    page.record = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",28);
    SDL_Color color_record = {0xff, 0xff, 0xff ,0xff};
    SDL_Surface *surface_record = TTF_RenderText_Blended(page.record, Score,color_record);
    SDL_Texture *texture_record = SDL_CreateTextureFromSurface(app.renderer, surface_record);

    //绘制初始方块和小狗
    square_remember = ".\\res\\pictures\\square6.png";
    new_square();
    draw_square();
    draw_dog();

    //配置音效
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,2048);
    page.chunk1 = Mix_LoadWAV(".\\res\\music\\chunk.ogg");

    //显示分数
    itoa(score, Score, 10);
    draw_score(SCORE_X, SCORE_Y);

    itoa(record, Record, 10);
    draw_record(RECORD_X, RECORD_Y);

    SDL_RenderPresent(app.renderer);

    while(1){
        while(SDL_PollEvent(&game)){
            SDL_RenderPresent(app.renderer);
            switch (game.type) {
                case SDL_KEYDOWN:
                    if(game.key.keysym.sym == SDLK_ESCAPE){
                        Mix_HaltMusic();
                        printf("Quit by ESC!\n");
                        //关闭背景
                        SDL_DestroyTexture(page.texture);

                        //关闭小狗
                        SDL_DestroyTexture(page.texture_image);

                        //关闭方块
                        SDL_DestroyTexture(page.texture_square);

                        SDL_DestroyTexture(page.texture_new_square);

                        //关闭文字
                        SDL_FreeSurface(surface_hint);
                        SDL_DestroyTexture(texture_hint);

                        //关闭得分
                        SDL_FreeSurface(surface_score);
                        SDL_DestroyTexture(texture_score);

                        //关闭记录
                        SDL_FreeSurface(surface_record);
                        SDL_DestroyTexture(texture_record);

                        TTF_CloseFont(page.font);

                        //关闭音效
                        Mix_FreeChunk(page.chunk1);
                        Mix_CloseAudio();

                        exit(0);
                    }
                case SDL_QUIT:
                    Mix_HaltMusic();
                    printf("Quit by SDL_QUIT!\n");
                    //关闭背景
                    SDL_DestroyTexture(page.texture);

                    //关闭小狗
                    SDL_DestroyTexture(page.texture_image);

                    //关闭方块
                    SDL_DestroyTexture(page.texture_square);

                    SDL_DestroyTexture(page.texture_new_square);

                    //关闭文字
                    SDL_FreeSurface(surface_hint);
                    SDL_DestroyTexture(texture_hint);

                    //关闭得分
                    SDL_FreeSurface(surface_score);
                    SDL_DestroyTexture(texture_score);

                    //关闭记录
                    SDL_FreeSurface(surface_record);
                    SDL_DestroyTexture(texture_record);

                    TTF_CloseFont(page.font);

                    //关闭音效
                    Mix_FreeChunk(page.chunk1);
                    Mix_CloseAudio();

                    exit(0);

                case SDL_MOUSEBUTTONDOWN:
                    printf("Mouse button down!\n");
                    Mix_PlayChannel(-1, page.chunk1, 0);//播放蓄力音乐

                    unsigned int start = SDL_GetTicks();//start_timing
                    break;

                case SDL_MOUSEBUTTONUP:
                    printf("Mouse button up!\n");
                    Mix_HaltChannel(-1);//中断蓄力 停止音乐

                    unsigned int time = SDL_GetTicks() - start;//end_timing
                    printf("%dms elapsed\n", time);

                    take_a_jump(time,20,440);//跳一跳
                    square_remember = square_rem;

                    //判断是否在方块上
                    if(is_centered()){//如果是的话，回到角落准备下一次蓄力，生成新的方块
                        printf("Centered!\n");

                        if(strcmp(square_rem, ".\\res\\pictures\\square21.png") == 0 || strcmp(square_rem, ".\\res\\pictures\\square22.png") == 0 || strcmp(square_rem, ".\\res\\pictures\\square23.png") == 0){
                            score += 20, cnt += 2;
                            //配置音频信息
                            int num = GetNum(3);
                            char *music = Point3[num];
                            page.chunk2 = Mix_LoadWAV(music);

                            printf("Play Surprise Music!\n");
                            Mix_PlayChannel(-1, page.chunk2, 0);

                            SDL_Delay(4000);

                            //关闭音频
                            Mix_HaltChannel(-1);
                            Mix_FreeChunk(page.chunk2);

                            //SDL_Delay(1500);
                        }
                        else{
                            score ++, cnt += 2;
                            SDL_Delay(1500);
                        }

                        if(score > record){
                            record = score;
                        }

                        printf("cnt ++\n");

                        itoa(score, Score, 10);
                        itoa(record, Record, 10);

                        back();

                        new_square();

                        continue;
                    }
                    else{//否则终止游戏，显示最终得分，和最高记录比较，修改最高记录
                        printf("You Lose!\n");

                        SDL_Delay(1500);

                        //关闭背景
                        SDL_DestroyTexture(page.texture);

                        //关闭小狗
                        SDL_DestroyTexture(page.texture_image);

                        //关闭方块
                        SDL_DestroyTexture(page.texture_square);

                        SDL_DestroyTexture(page.texture_new_square);

                        //关闭文字
                        SDL_FreeSurface(surface_hint);
                        SDL_DestroyTexture(texture_hint);

                        //关闭得分
                        SDL_FreeSurface(surface_score);
                        SDL_DestroyTexture(texture_score);

                        //关闭记录
                        SDL_FreeSurface(surface_record);
                        SDL_DestroyTexture(texture_record);

                        TTF_CloseFont(page.font);

                        //关闭音效
                        Mix_FreeChunk(page.chunk1);
                        Mix_CloseAudio();

                        if(score > record_rem) {
                            record_rem = score;
                            break_the_record();
                        }

                        else{
                            Lose();
                        }
                        break;
                    }
            }
        }
        //SDL_Delay(50);
    }
}

void draw_render(){
    //游戏背景图
    page.texture = IMG_LoadTexture(app.renderer, ".\\res\\pictures\\game.jpg");
    SDL_RenderCopy(app.renderer, page.texture, NULL, NULL);
}

void draw_square(){
    //显示方块
    page.texture_square = IMG_LoadTexture(app.renderer, square_remember);
    SDL_Rect rect_square = {.x = 0, .y = 465, .w = W - cnt, .h = H - cnt};
    SDL_RenderCopy(app.renderer, page.texture_square, NULL, &rect_square);
    SDL_RenderPresent(app.renderer);
}

void draw_dog(){
    //显示小狗
    page.texture_image = IMG_LoadTexture(app.renderer, ".\\res\\pictures\\line_puppy1.png");
    SDL_Rect rect_image1 = {.x = 20, .y = 440};
    SDL_QueryTexture(page.texture_image, NULL, NULL, &rect_image1.w, &rect_image1.h);
    SDL_RenderCopy(app.renderer, page.texture_image, NULL, &rect_image1);
    SDL_RenderPresent(app.renderer);
}

bool is_centered(){
    if(abs(newX - loc_square_x) <= 55 - cnt / 2 && (newY + 25) - loc_square_y <= 45 - cnt / 2 )
        return true;
    else
        return false;
}

void back() {
    printf("Back!\n");
    for(int x = newX,y = newY; y <= 440; x -= 10, y += 10){
        SDL_RenderClear(app.renderer);
        draw_render();
        draw_score(SCORE_X, SCORE_Y);
        draw_record(RECORD_X, RECORD_Y);

        page.texture_square = IMG_LoadTexture(app.renderer, square_rem);
        SDL_Rect rect_square1 = {.x = x - 27, .y = y + 30,.w = W - cnt, .h = H - cnt };
        SDL_RenderCopy(app.renderer, page.texture_square, NULL, &rect_square1);
        SDL_RenderPresent(app.renderer);

        page.texture_image = IMG_LoadTexture(app.renderer, ".\\res\\pictures\\line_puppy1.png");
        SDL_Rect rect_image1 = {.x = x, .y = y};
        SDL_QueryTexture(page.texture_image, NULL, NULL, &rect_image1.w, &rect_image1.h);
        SDL_RenderCopy(app.renderer, page.texture_image, NULL, &rect_image1);

        SDL_RenderPresent(app.renderer);
        SDL_Delay(1000/90);

        //关闭背景
        SDL_DestroyTexture(page.texture);

        //关闭小狗
        SDL_DestroyTexture(page.texture_image);

        //关闭方块
        SDL_DestroyTexture(page.texture_square);

        TTF_CloseFont(page.record);
        TTF_CloseFont(page.score);
    }

}

void take_a_jump(unsigned int time,int initX, int initY){
    newX = initX + (int)time / 20,newY = initY - (int)time/20;
    for(int x = initX, y = initY; y >= newY; x += 10, y -= 10){//x = 20, y = 440
        SDL_RenderClear(app.renderer);
        draw_render();
        draw_score(SCORE_X, SCORE_Y);
        draw_record(RECORD_X, RECORD_Y);

        page.texture_square = IMG_LoadTexture(app.renderer, square_rem);
        SDL_Rect rect_square1 = {.x = loc_square_x, .y = loc_square_y ,.w = W - cnt, .h = H - cnt};
        SDL_RenderCopy(app.renderer, page.texture_square, NULL, &rect_square1);

        draw_square();

        int num = GetNum(2);
        image_rem = Point2[num];
        page.texture_image = IMG_LoadTexture(app.renderer, image_rem);
        SDL_Rect rect_image1 = {.x = x, .y = y};
        SDL_QueryTexture(page.texture_image, NULL, NULL, &rect_image1.w, &rect_image1.h);
        SDL_RenderCopy(app.renderer, page.texture_image, NULL, &rect_image1);

        SDL_RenderPresent(app.renderer);
        SDL_Delay(1000/90);

        //关闭背景
        SDL_DestroyTexture(page.texture);

        //关闭小狗
        SDL_DestroyTexture(page.texture_image);

        //关闭方块
        SDL_DestroyTexture(page.texture_square);

        //关闭文字
        TTF_CloseFont(page.record);
        TTF_CloseFont(page.score);
    }
}

int GetNum(int i){
    srand((unsigned)time(NULL));
    return rand() % i;  // 生成0-22的随机数
}

void new_square(){
    int random_num = GetNum(23);
    square_rem = Point[random_num];

    page.texture_new_square = IMG_LoadTexture(app.renderer, square_rem);

    loc_square_x = 50 + GetNum(23) * 5, loc_square_y = 410 - GetNum(23) * 5;
    SDL_Rect new_square = {.x = loc_square_x, .y = loc_square_y,.w = W - cnt, .h = H - cnt };
    SDL_RenderCopy(app.renderer, page.texture_new_square, NULL, &new_square);

    SDL_RenderPresent(app.renderer);
}

void draw_score(int x, int y){
    //显示得分
    page.score = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",28);
    SDL_Color color_score = {0x3f, 0x5f, 0x4f ,0xff};
    SDL_Surface *surface_score = TTF_RenderText_Blended(page.score, Score,color_score);
    SDL_Texture *texture_score = SDL_CreateTextureFromSurface(app.renderer, surface_score);
    SDL_Rect rect_hint = {.x = x, .y = y};
    SDL_QueryTexture(texture_score, NULL, NULL, &rect_hint.w, &rect_hint.h);
    SDL_RenderCopy(app.renderer, texture_score,NULL, &rect_hint);
}

void draw_record(int x, int y){
    //显示得分
    page.record = TTF_OpenFont(".\\res\\fonts\\Cute-Aurora-2.ttf",28);
    SDL_Color color_record = {0x3f, 0x5f, 0x4f ,0xff};
    SDL_Surface *surface_record = TTF_RenderText_Blended(page.record, Record,color_record);
    SDL_Texture *texture_record = SDL_CreateTextureFromSurface(app.renderer, surface_record);
    SDL_Rect rect_record = {.x = x, .y = y};
    SDL_QueryTexture(texture_record, NULL, NULL, &rect_record.w, &rect_record.h);
    SDL_RenderCopy(app.renderer, texture_record,NULL, &rect_record);
}