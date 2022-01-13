#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "debugmalloc.h"
#include "SDL_rajzok.h"

/* kirajzol egy aknakereső mezőt; a forrás a betöltött kép, a cél helyére rajzol.
  melyik képet, milyen koordinatakra: melyik, x, y.*/
void mezo_rajzol(SDL_Renderer *renderer, SDL_Texture *mezok, Mezokep melyik, int x, int y, int LEVEL) {
    /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
    SDL_Rect src = { (melyik % 7) * 200, (melyik / 7) * 200, MERET, MERET };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { x, y, LEVEL, LEVEL };
    /* kepreszlet masolasa*/
    SDL_RenderCopy(renderer, mezok, &src, &dest);
}

void EASY_rajzol(SDL_Renderer *renderer, SDL_Texture *mezok) {

    /* Megrajzolja a kiválasztott pályaméretre a Lefordított aknamezőt*/
    for (int i = 20 ; i < 380 ; i = i+EASY){
        for (int j = 60 ; j < 420 ; j = j + EASY){
                mezo_rajzol(renderer , mezok , Leforditott , i , j, EASY);
        }
    }
       /*  a pálya kerete, fentről 60 pixel a többi oldalon meg 20 pixeles sáv*/
    boxRGBA(renderer, 0, 0, 19, 440, 160, 160, 160, 255);
    boxRGBA(renderer, 380, 0, 400, 440, 160, 160, 160, 255);
    boxRGBA(renderer, 0, 0, 400, 59, 160, 160, 160, 255);
    boxRGBA(renderer, 0, 420, 400, 440, 160, 160, 160, 255);
}

void INTERMEDIATAE_rajzol(SDL_Renderer *renderer, SDL_Texture *mezok) {

    /* Megrajzolja a kiválasztott pályaméretre a Lefordított aknamezőt*/
    for (int i = 20 ; i < 500 ; i = i+INTERMEDIATE){
        for (int j = 60 ; j < 540 ; j = j + INTERMEDIATE){
                mezo_rajzol(renderer , mezok , Leforditott , i , j, INTERMEDIATE);
        }
    }
      /*   a pálya kerete, fentről 60 pixel a többi oldalon meg 20 pixeles sáv */
    boxRGBA(renderer, 0, 0, 19, 560, 160, 160, 160, 255);
    boxRGBA(renderer, 500, 0, 520, 560, 160, 160, 160, 255);
    boxRGBA(renderer, 0, 0, 520, 59, 160, 160, 160, 255);
    boxRGBA(renderer, 0, 540, 520, 560, 160, 160, 160, 255);
}

void HARD_rajzol(SDL_Renderer *renderer, SDL_Texture *mezok) {

    /* Megrajzolja a kiválasztott pályaméretre a Lefordított aknamezőt*/
    for (int i = 20 ; i < 340 ; i = i+HARD){
        for (int j = 60 ; j < 700 ; j = j + HARD){
                mezo_rajzol(renderer , mezok , Leforditott , i , j, HARD);
        }
    }

    /* a pálya kerete, fentről 60 pixel a többi oldalon meg 20 pixeles sáv */
    boxRGBA(renderer, 0, 0, 19, 720, 160, 160, 160, 255);
    boxRGBA(renderer, 340, 0, 360, 720, 160, 160, 160, 255);
    boxRGBA(renderer, 0, 0, 360, 59, 160, 160, 160, 255);
    boxRGBA(renderer, 0, 700, 360, 720, 160, 160, 160, 255);
}

void menu(SDL_Window *window, SDL_Renderer *renderer){
     /*  A menürendszer */
    /* Visszaállítja a menü méretét és úrjarajzolja azt */
    SDL_SetWindowSize(window, 520, 720);
    boxRGBA(renderer, 0, 0, 520, 720, 0, 0, 0, 255);
    boxRGBA(renderer, 50, 30, 470, 120, 160, 160, 160, 255);
    stringRGBA(renderer, 100, 75,"Easy", 0, 0, 0, 255);
    boxRGBA(renderer, 50, 165, 470, 255, 160, 160, 160, 255);
    stringRGBA(renderer, 100, 210,"Intermediate", 0, 0, 0, 255);
    boxRGBA(renderer, 50, 300, 470, 390, 160, 160, 160, 255);
    stringRGBA(renderer, 100, 345,"Hard", 0, 0, 0, 255);
    boxRGBA(renderer, 50, 435, 470, 525, 160, 160, 160, 255);
    stringRGBA(renderer, 100, 480,"Leaderboard", 0, 0, 0, 255);
   // boxRGBA(renderer, 435, 50, 525, 670, 160, 160, 160, 255);
   // stringRGBA(renderer, 480, 100,"Custom", 0, 0, 0, 255);   <--- Ha lesz idő, akkor ilyen is lesz.

}

Mezokep milyen (int x, int y, Mezo **tomb){

/* A megfelelő Mezokep elemmel tér vissza, amilyen a kattintott tömbelem értéke*/
/* Nem tudtam megoldani hirtelen máshogy csak ennyi if-el*/
if (!tomb[y][x].zaszlos_e){
    if (tomb[y][x].szam == -1){
            return Bomba;
    }
    if (tomb[y][x].szam == 0){
            return Nullas;
    }
    if (tomb[y][x].szam == 1){
            return Egyes;
    }
    if (tomb[y][x].szam == 2){
            return Kettes;
    }
    if (tomb[y][x].szam == 3){
            return Harmas;
    }
    if (tomb[y][x].szam == 4){
            return Negyes;
    }
    if (tomb[y][x].szam == 5){
            return Otos;
    }
    if (tomb[y][x].szam == 6){
            return Hatos;
    }
    if (tomb[y][x].szam == 7){
            return Hetes;
    }
    if (tomb[y][x].szam == 8){
            return Nyolcas;
    }
}
/* Ha már fel van fordítva a mező, de újból rákattintunk, akkor nem írja át valami másra*/
return -1;
}

void rajzol (SDL_Renderer* renderer, SDL_Texture *mezok, int szeles, int magas, int x, int y, int LEVEL, Mezo **tomb){


    if (x >= 20 && y >= 60 && x < szeles - 19 && y < magas - 19){
                int tombx = (x-20)/LEVEL;
                int tomby = (y-60)/LEVEL;

        if (tomb[tomby][tombx].leforditott && !tomb[tomby][tombx].zaszlos_e){

                mezo_rajzol(renderer, mezok, milyen(tombx, tomby, tomb), (x - ((x-20)%LEVEL)) , (y - ((y-60)%LEVEL)), LEVEL);
                tomb[tomby][tombx].leforditott = false;

                /* A rekurzív függvény, ami óramutató járásában nyitja az összes 0-ást*/
                if (milyen(tombx, tomby, tomb) == Nullas){
                    rajzol(renderer, mezok, szeles, magas, x - LEVEL, y - LEVEL, LEVEL, tomb);
                    rajzol(renderer, mezok, szeles, magas, x -LEVEL, y, LEVEL, tomb);
                    rajzol(renderer, mezok, szeles, magas, x - LEVEL, y + LEVEL, LEVEL, tomb);

                    rajzol(renderer, mezok, szeles, magas, x, y + LEVEL, LEVEL, tomb);

                    rajzol(renderer, mezok, szeles, magas, x + LEVEL, y + LEVEL, LEVEL, tomb);
                    rajzol(renderer, mezok, szeles, magas, x + LEVEL, y, LEVEL, tomb);
                    rajzol(renderer, mezok, szeles, magas, x + LEVEL, y - LEVEL, LEVEL, tomb);

                    rajzol(renderer, mezok, szeles, magas, x, y - LEVEL, LEVEL, tomb);
                }
        }
    }

    else return;
}

void felrobbant (SDL_Renderer* renderer, SDL_Texture *mezok, int sizex, int sizey, int ablak_x, int ablak_y, int LEVEL, Mezo **tomb){

        /* Kirajzolja az összes meg nem jelölt bombát*/
            for (int a = 0 ; a < sizex ; a ++){
                    for (int b = 0 ; b < sizey ; b++){
                            if (milyen(a, b, tomb) == Bomba){
                                    mezo_rajzol(renderer, mezok, Bomba, a * LEVEL + 20, b * LEVEL + 60, LEVEL);
                            }

                            /* Ha rossz helyen van egy zászló, amikor bomba fordul fel, akkor áthúzza a rossz zászlót */
                            if (tomb[b][a].szam != -1 && tomb[b][a].zaszlos_e)
                            mezo_rajzol(renderer, mezok, Rosszzaszlo, a * LEVEL + 20, b * LEVEL + 60, LEVEL);

                    }
            }

                        /* Kirajzolja a menube visszatérő gombot*/
                        boxRGBA(renderer, (ablak_x/2) - 50, (ablak_y/2) - 30, (ablak_x/2) + 50, (ablak_y/2) + 30, 160, 160, 160, 255);
                        stringRGBA(renderer, (ablak_x/2) - 35 , (ablak_y/2) - 20, "Game over", 0, 0, 0, 255);
                        stringRGBA(renderer,(ablak_x/2) - 46 , (ablak_y/2) + 8, "Back to menu", 0, 0, 0, 255);

}


/* Az ablak megnyitó függvény*/
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

