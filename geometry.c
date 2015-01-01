/* gcc geometryc.c -lSDL -lSDL_gfx -lm */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#define COLOR 0x5bb3b540 //色 0xrrggbbaa
#define SIZE 600 //ウィンドウのサイズ アイコン等のために正方形
#define CUT 44.0 //2πをCUT等分
#define RAD 3.14*2/CUT //°をラジアンに

SDL_Surface *WINDOW;

void Draw_Geometry()
{
    char r[] = { 1, 4, 10, 44, 100 }; //ここを変えると楽しい！
    int i, j, NUM = strlen(r), flag = 1;

    while( flag ){
        SDL_FillRect(WINDOW, NULL, 0xffffffff);

        for( i = 0; i < NUM; ++i )
            for( j = 0; j < CUT; ++j )
                circleColor(WINDOW, SIZE/2+cos(j*RAD)*r[i], SIZE/2+sin(j*RAD)*r[i], r[i], COLOR);

        SDL_UpdateRect(WINDOW, 0, 0, 0, 0);

        printf("quit 'q'\n");
        char ch = getchar(); scanf("%*c");
        if( ch == 'q' ) flag = 0;
    }
}

void View_Geometry()
{
    int i, j, NUM = rand() % 100, flag = 1;
    char r[NUM];

    for( i = 0; i < NUM; ++i )
        r[i] = rand() % 256;

    while( flag ){
        SDL_FillRect(WINDOW, NULL, 0xffffffff);

        for( i = 0; i < NUM; ++i )
            for( j = 0; j < CUT; ++j ){
                circleColor(WINDOW, SIZE/2+cos(j*RAD)*r[i], SIZE/2+sin(j*RAD)*r[i], r[i], COLOR);
                SDL_UpdateRect(WINDOW, 0, 0, 0, 0);
                SDL_Delay(1000);
            }

        printf("quit->'q' restart->'r'\n");
        char ch = getchar(); scanf("%*c");
        switch( ch ){
        case 'q': flag = 0; break;
        case 'r': SDL_FillRect(WINDOW, NULL, 0xffffff); break;
        default : break;
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

    printf("draw -> 'd'  view -> 'v'\n");
    char ch = getchar(); scanf("%*c");
    switch( ch ){
    case 'd': Draw_Geometry(); break;
    case 'v': View_Geometry(); break;
    default : break;
    }

    //メモリ解放
    SDL_FreeSurface(WINDOW);

    //SDLライブラリを閉じる
    SDL_Quit();

    return 0;
}
