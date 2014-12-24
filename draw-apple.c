#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#define NUM_GENE 96
#define NUM_CHROM 6
#define WIDTH 600
#define HEIGHT 400

typedef struct {
    char gene[NUM_GENE];
    int fitness;
} chrom;

chrom current[NUM_CHROM], next[NUM_CHROM];
SDL_Surface *window;
SDL_Rect place[NUM_CHROM] = { { 0, 0 }, { 200, 0 }, { 400, 0 }, { 200, 0 }, { 200, 200 }, { 200, 400 } };


int print_error(const char *str);
void create();
int sdl_init();
void sdl_quit();

int main()
{
    int flag = 1;

    srand(time(0));

    if( sdl_init() < 0 ) exit(-1);

    create();

    while( flag ){
        draw_window();

    }

    sdl_quit();

    return 0;
}

int print_error(const char *str)
{
    fprintf(stderr, "%s\n", str);
    return -1;
}

void create()
{
    int i, j;

    for( i = 0; i < NUM_CHROM; ++i )
        for( j = 0; j < NUM_GENE; ++i )
            current[i].gene[j] = rand() & 1;
}

int sdl_init()
{
    //SDL初期化
    if( SDL_Init(SDL_INITEVERYTHING) < 0 )
        return print_error(SDL_GetError());

    //ウィンドウ生成
    window = SDL_VideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
    if( NULL == window )
        return print_error(SDL_GetError());

    //ウィンドウに名前を付ける
    SDL_WM_SetCaption("draw-apple", "draw-apple");

    //入力の焦点を制限しない
    SDL_WM_GrabInput(SDL_GRAB_OFF);

    return 0;
}

void sdl_quit()
{
    //メモリ解放
    SDL_FreeSurface(window);

    //SDLライブラリを閉じる
    SDL_Quit();
}

//ここからだよー
void draw_window()
{
    Sint16 n = b2i();
}
