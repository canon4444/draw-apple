draw-apple
==========
[SDL(Simple DirectMedia Layer)][2]を利用して，林檎の絵（という名の赤玉）を描きます．

SDLをこのディレクトリには含みません．  
各自でお願いします．

draw-apple.c -> 林檎の絵を描きます．(本筋)  
random_geometry.c -> ランダムに以下に記述している図形の内，線画のものを描画します．  
geometry.c -> 任意の幾何学模様またはランダムに幾何学模様を描画します．

[@hat_404][1]

[1]: https://twitter.com/hat_404 "@hat_404"
[2]: http://www.libsdl.org/ "SDL(Simple DirectMedia Layer)"

==
設計的な何か

図形(-lSDL_gfx)(#include \<SDL/SDL_gfxPrimitives.h\>)
+ 水平線[hlineColor(SDL_Surface *, x_s, x_g, y, 0xrrggbbff)]
+ 垂直線[vlineColor(SDL_Surface *, x, y_s, y_g, 0xrrggbbff)]
+ 四角形線画[rectangleColor(SDL_Surface *, x_s, y_s, x_g, y_g, 0xrrggbbff)]
+ 四角形[boxColor(SDL_Surface *, x_s, y_s, x_g, y_g, 0xrrggbbff)]
+ 直線[lineColor(SDL_Surface *, x_s, y_s, x_g, y_g, 0xrrggbbff)]
+ 円線画[circleColor(SDL_Surface *, x, y, r, 0xrrggbbff)]
+ 円[filledCircleColor(SDL_Surface *, x, y, r, 0xrrggbbff)]
+ 半円線画[pieColor(SDL_Surface *, x, y, r, theta_s, theta_g, 0xrrggbbff)]
+ 半円[filledPieColor(SDL_Surface *, x, y, r, theta_s, theta_g, 0xrrggbbff)]
+ 三角形線画[trigonColor(SDL_Surface *, x_1, y_1, x_2, y_2, x_3, y_3, 0xrrggbbff)]
+ 三角形[filledTrigonColor(SDL_Surface *, x_1, y_1, x_2, y_2, x_3, y_3, 0xrrggbbff)]
+ 合計11種類 1011

色
+ rrrr rrrr gggg gggg bbbb bbbb 1111 1111

x, y, theta -> Sint16
+ xxxx xxxx xxxx xxxx, yyyy yyyy yyyy yyyy, tttt tttt tttt tttt

[kkkk(図形指定)] [Sint16 * 3 (hlineColor)] [Sint16 * 3 (vlineColor)] [Sint16 * 4 (rectangleColor)] [Sint16 * 4 (boxColor)] [Sint16 * 4 (lineColor)] [Sint16 * 3 (circleColor)] [Sint16 * 3 (filledCircleColor)] [Sint16 * 5 (pieColor)] [Sint16 * 5 (filledPieColor)] [Sint16 * 6 (trigonColor)] [Sint16 * 6 (filledTrigonColor)] [Color]  
合計764bit=95.5byte(α値含まず)  
合計768bit=96byte(α値含む)  
