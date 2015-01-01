/* gcc life_game.c -lSDL -lSDL_gfx */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#define WIDTH  1232
#define HEIGHT 659

void lifegame(SDL_Surface *window)
{
    srand(time(0));

    /*
     * N height
     * M width
     * LIMIT 最大ループ回数
     * delayTime 一時停止時間[mili second]
     */
    const int N = window->h / 8, M = window->w / 8, n = N - 1, m = M - 1, LIMIT = 1001, delayTime = 100;
    int table[N][M], nexttable[N][M];
    int i, j;

    /* 個体生成 */
    for ( i = 0; i < N; ++i )
        for ( j = 0; j < M; ++j )
            table[i][j] = rand() % 2;

    /* Life Game */
    int lim = 0; /* 何回繰り返すか */
    while ( ++lim < LIMIT ) {
        /* 描画 */
        /* 背景 白色 0xffffffff */
        SDL_FillRect(window, NULL, 0xffffffff);
        for ( i = 0; i < N; ++i )
            for ( j = 0; j < M; ++j )
                if ( table[i][j] ) {
                    int width = 8 * j, height = 8 * i;
                    /* マス 新橋色 0x5bb3b540 */
                    boxColor(window, width, height, width+8, height+8, 0x5bb3b5ff);
                    /* 枠 白色 0xffffffff */
                    rectangleColor(window, width, height, width+8, height+8, 0xffffffff);
                }

        /* 更新 */
        SDL_UpdateRect(window, 0, 0, 0, 0);
        SDL_Delay(delayTime);

        /* 判定 */
        /*
         * cnt 周囲の個体数
         * bit そのマスが端にあるかどうか
         */
        int cnt, bit;
        for ( i = 0; i < N; ++i )
            for ( j = 0; j < M; ++j ) {

                cnt = 0, bit = 0;

                if ( i == n ) bit |= 4; /* 最下一列 */
                else if ( i != 0 ) bit |= 8; /* 最上一列以外 */

                if ( j == m ) bit |= 1; /* 最右一列 */
                else if ( j != 0 ) bit |= 2; /* 最左一列以外 */

                switch ( bit ) {
                case 10 : /* 外周1マスより内側 */
                    cnt += table[i-1][j-1];
                    cnt += table[i-1][j];
                    cnt += table[i-1][j+1];
                    cnt += table[i][j-1];
                    cnt += table[i][j+1];
                    cnt += table[i+1][j-1];
                    cnt += table[i+1][j];
                    cnt += table[i+1][j+1];
                    break;
                case 9 : /* 最右 真中 */
                    cnt += table[i-1][j-1];
                    cnt += table[i-1][j];
                    cnt += table[i][j-1];
                    cnt += table[i+1][j-1];
                    cnt += table[i+1][j];
                    break;
                case 8 : /* 最左 真中 */
                    cnt += table[i-1][j];
                    cnt += table[i-1][j+1];
                    cnt += table[i][j+1];
                    cnt += table[i+1][j];
                    cnt += table[i+1][j+1];
                    break;
                case 6 : /* 最下 真中 */
                    cnt += table[i-1][j-1];
                    cnt += table[i-1][j];
                    cnt += table[i-1][j+1];
                    cnt += table[i][j-1];
                    cnt += table[i][j+1];
                    break;
                case 5 : /* 最右 最下 : 右下 */
                    cnt += table[i-1][j-1];
                    cnt += table[i-1][j];
                    cnt += table[i][j-1];
                    break;
                case 4 : /* 最下 最左 : 左下 */
                    cnt += table[i-1][j];
                    cnt += table[i-1][j+1];
                    cnt += table[i][j+1];
                    break;
                case 2 : /* 最上 真中 */
                    cnt += table[i][j-1];
                    cnt += table[i][j+1];
                    cnt += table[i+1][j-1];
                    cnt += table[i+1][j];
                    cnt += table[i+1][j+1];
                    break;
                case 1 : /* 最上 最右 : 右上 */
                    cnt += table[i][j-1];
                    cnt += table[i+1][j-1];
                    cnt += table[i+1][j];
                    break;
                case 0 : /* 最上 最左 : 左上 */
                    cnt += table[i][j+1];
                    cnt += table[i+1][j];
                    cnt += table[i+1][j+1];
                    break;
                default :
                    printf("error\n");
                    lim = LIMIT;
                }

                if ( cnt < 2 ) nexttable[i][j] = 0; /* 過疎 */
                else if ( cnt > 3 ) nexttable[i][j] = 0; /* 過密 */
                else if ( cnt == 3 ) nexttable[i][j] = 1; /* 誕生 */
            }

        /* テーブル移し替え */
        for ( i = 0; i < N; ++i )
            for ( j = 0; j < M; ++j )
                table[i][j] = nexttable[i][j];

        /* 全滅しているか */
        int count = 0;
        for ( i = 0; i < N; ++i )
            for ( j = 0; j < N; ++j )
                count += table[i][j] & 1;
        if ( count == 0 )
            lim = LIMIT;
    }
}

int main()
{
    /* SDL 初期化 */
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
        printf("fail to INIT\n");
        exit(-1);
    }

    /* ウィンドウ生成 */
    SDL_Surface *window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
    if ( window == NULL ) {
        printf( "fail to create the window! \n" );
        exit(-1);
    }

    /* ウィンドウ，アイコンを命名 */
    SDL_WM_SetCaption("Hello world!", "Life Game");

    /* 入力をウィンドウ内に収める : ON / OFF / QUERY */
    /* ON を while ( 1 ) で実行すると成す術がなくなるので注意（経験者は語る） */
    SDL_WM_GrabInput(SDL_GRAB_OFF);

    lifegame(window);

    /* Surface * を解放 */
    SDL_FreeSurface(window);

    /* SDL ライブラリの使用終了 */
    SDL_Quit();

    return 0;
}
