/* gcc random_geometry.c -lSDL -lSDL_gfx */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#define COLOR 0x5bb3b540
#define SIZE 600
#define AXIS rand() % SIZE
#define THETA rand() % 360

SDL_Surface *WINDOW;

void Draw_Geometry()
{
    int flag = 1;

    SDL_FillRect(WINDOW, NULL, 0xffffffff);
    while( flag ){
        switch( rand() % 7 ){
        case 0: hlineColor(WINDOW, AXIS, AXIS, AXIS, COLOR); break;
        case 1: vlineColor(WINDOW, AXIS, AXIS, AXIS, COLOR); break;
        case 2: rectangleColor(WINDOW, AXIS, AXIS, AXIS, AXIS, COLOR); break;
        case 3: lineColor(WINDOW, AXIS, AXIS, AXIS, AXIS, COLOR); break;
        case 4: circleColor(WINDOW, AXIS, AXIS, AXIS, COLOR); break;
        case 5: pieColor(WINDOW, AXIS, AXIS, AXIS, THETA, THETA, COLOR); break;
        case 6: trigonColor(WINDOW, AXIS, AXIS, AXIS, AXIS, AXIS, AXIS, COLOR); break;
        default: break;
        }
        SDL_UpdateRect(WINDOW, 0, 0, 0, 0);

        printf("again->'a' reset->'r' exit->'e'\n");
        char ch = getchar(), c = getchar();
        switch( ch ){
        case 'a': flag = 1; break;
        case 'r': SDL_FillRect(WINDOW, NULL, 0xffffffff); break;
        case 'e': flag = 0; break;
        default : flag = 1; break;
        }
    }
}

int main()
{
    srand(time(0));

    //SDL初期化
    if( SDL_Init(SDL_INIT_EVERYTHING) ){
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(-1);
    }

    //ウィンドウ生成
    WINDOW = SDL_SetVideoMode(SIZE, SIZE, 32, SDL_SWSURFACE);
    if( WINDOW == NULL ){
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(-1);
    }

    Draw_Geometry();

    //メモリ解放
    SDL_FreeSurface(WINDOW);

    //SDLライブラリを閉じる
    SDL_Quit();

    return 0;
}
