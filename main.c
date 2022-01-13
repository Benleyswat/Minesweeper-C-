#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "SDL_rajzok.h"
#include "2dimtomb.h"
#include "fileba.h"
#include "debugmalloc.h"




int main(int argc, char *argv[]) {

    /* ablak létrehozása */
    SDL_Window *window;
    SDL_Renderer *renderer;
    int ablak_x = 520;
    int ablak_y = 720;
    sdl_init("NHazi-Aknakereso", ablak_x, ablak_y, &window, &renderer);

    /* kep betoltese */
    SDL_Texture *mezok = IMG_LoadTexture(renderer, "mezo.png");
    if (mezok == NULL) {
        SDL_Log("Nincs ilyen kepfajl: %s", IMG_GetError());
        exit(1);
    }


    /* Az első alkalommal megrajzolja a menüt */

    menu(window, renderer);
    srand(time(0));

    ///////////////////////////* Az esemenyvezerelt hurok: az egér használata és működésének leírása *///////////////////////////////////////////////////


    bool quit = false;
    bool rclick = false;
    bool lclick = false;
    bool firstclick = false;
    bool rangsor = false;
    bool general = false;
    bool game_over = false;
    Mezo **tomb = NULL;
    int LEVEL;
    int sizex, sizey, bomb, zaszlok, rajzolt_zaszlo;
        while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        time_t kezdet;

        switch (event.type) {

            case SDL_MOUSEBUTTONDOWN:

                /* A BAL Egérgomb működése az egyes részekven */

                if (event.button.button == SDL_BUTTON_LEFT) {

///////////////////////////////////////////////////////////     Menürendszer    ////////////////////////////////////////////////////////////

                    /* A menübe marad a program amíg nem kattintunk az egyik pályára */
                    if (!firstclick){

                            /* Ha a EASY gombra kattintassz, legenerálja a lefordított mezőket és beállítja a megfelelő változókat */
                            if (event.button.x > 50 && event.button.x < 470 && event.button.y > 30 && event.button.y < 120 && !rangsor) {
                                        firstclick = true;
                                        lclick = true;
                                        sizex = 9;
                                        sizey = 9;
                                        bomb = 10;
                                        zaszlok = 0;
                                        LEVEL = EASY;
                                        ablak_x = sizex*LEVEL + 40;
                                        ablak_y = sizey*LEVEL + 80;
                                        SDL_SetWindowSize(window, ablak_x, ablak_y);
                                        EASY_rajzol(renderer, mezok);
                                        /* A tomb lefoglalása, amiben a random bombák és szamok lesznek*/
                                        tomb = tomb_lefoglal(sizex, sizey);

                                }

                            /* Ha a INTERMEDIATE gombra kattintassz, legenerálja a lefordított mezőket és beállítja a megfelelő változókat */
                            else if (event.button.x > 50 && event.button.x < 470 && event.button.y > 165 && event.button.y < 255 && !rangsor) {
                                        firstclick = true;
                                        lclick = true;
                                        sizex = 16;
                                        sizey = 16;
                                        bomb = 40;
                                        zaszlok = 0;
                                        LEVEL = INTERMEDIATE;
                                        ablak_x = sizex*LEVEL + 40;
                                        ablak_y = sizey*LEVEL + 80;
                                        SDL_SetWindowSize(window, ablak_x, ablak_y);
                                        INTERMEDIATAE_rajzol(renderer, mezok);
                                        /* A tomb lefoglalása, amiben a random bombák és szamok lesznek*/
                                        tomb = tomb_lefoglal(sizex, sizey);

                                }

                            /* Ha a HARD gombra kattintassz, legenerálja a lefordított mezőket és beállítja a megfelelő változókat */
                            else if (event.button.x > 50 && event.button.x < 470 && event.button.y > 300 && event.button.y < 390 && !rangsor) {
                                        firstclick = true;
                                        lclick = true;
                                        sizex = 16;
                                        sizey = 32;
                                        bomb = 99;
                                        zaszlok = 0;
                                        LEVEL = HARD;
                                        ablak_x = sizex*LEVEL + 40;
                                        ablak_y = sizey*LEVEL + 80;
                                        SDL_SetWindowSize(window, ablak_x, ablak_y);
                                        HARD_rajzol(renderer, mezok);
                                        /* A tomb lefoglalása, amiben a random bombák és szamok lesznek*/
                                        tomb = tomb_lefoglal(sizex, sizey);
                                }

                            /* Belép a ranglistába, ami kiírja a 3 pálya legjobb időit*/
                            else if (event.button.x > 50 && event.button.x < 470 && event.button.y > 435 && event.button.y < 525 && !rangsor){
                                        lclick = true;
                                        rangsor = true;
                                        boxRGBA(renderer, 0, 0, ablak_x, ablak_y, 0, 0, 0, 255);
                                        stringRGBA(renderer, 200, 30, "Leaderboard", 255, 255, 255, 255);


                                        /* A következő 70 sot megpróbáltam függvénykénybe beírni, de nem akart úgy működni*/
                                        /* Itt beolvassa a megfelelő fájlokból a legjobb időket*/
                                        /* Majd azokat formázva ki is írja a leaderboard fülben*/
                                        FILE *fp;
                                        char legjobb[10];
                                        int mili;
                                        char second[7];
                                        char milisecond[4];
                                        char kiir[20];

                                            fp = fopen("Easy.txt", "rt");

                                            fgets(legjobb, 10, fp);

                                            fclose(fp);

                                            if (strlen(legjobb) > 3){
                                                    mili = atoi(legjobb);


                                                    sprintf(second, "%d", mili/1000);
                                                    sprintf(milisecond, "%d", mili%1000);


                                                    strcpy(kiir, second);
                                                    strcat(kiir, ".");
                                                    strcat(kiir, milisecond);
                                                    strcat(kiir, " seconds");

                                                stringRGBA(renderer, 100, 135, "Easy: ", 255, 255, 255, 255);
                                                stringRGBA(renderer, 150, 135, kiir, 255, 255, 255, 255);

                                            }
                                            fp = fopen("Intermediate.txt", "rt");

                                            fgets(legjobb, 10, fp);

                                            fclose(fp);

                                            mili = atoi(legjobb);

                                            sprintf(second, "%d", mili/1000);
                                            sprintf(milisecond, "%d", mili%1000);

                                            strcpy(kiir, second);
                                            strcat(kiir, ".");
                                            strcat(kiir, milisecond);
                                            strcat(kiir, " seconds");

                                        stringRGBA(renderer, 100, 210, "Intermediate: ", 255, 255, 255, 255);
                                        stringRGBA(renderer, 220, 210, kiir, 255, 255, 255, 255);


                                            fp = fopen("Hard.txt", "rt");

                                            fgets(legjobb, 10, fp);

                                            fclose(fp);

                                            mili = atoi(legjobb);

                                            sprintf(second, "%d", mili/1000);
                                            sprintf(milisecond, "%d", mili%1000);


                                            strcpy(kiir, second);
                                            strcat(kiir, ".");
                                            strcat(kiir, milisecond);
                                            strcat(kiir, " seconds");

                                        stringRGBA(renderer, 100, 285, "Hard: ", 255, 255, 255, 255);
                                        stringRGBA(renderer, 150, 285, kiir, 255, 255, 255, 255);


                            }
                            /* Visszatérés a menübe a ranglistából*/
                            else if (rangsor){
                                        menu(window, renderer);
                                        lclick = true;
                                        rangsor = false;
                            }

                            /* Ha nem a gombokra kattintunk, akkor vár, hogy gombra az egyik gombra kattints */
                            else{
                                        menu(window, renderer);
                                        lclick = true;
                            }
                    }

////////////////////////////////////////////////////////////////    GAME    //////////////////////////////////////////////////////////////////////

                    /* A kiválaszott játékmódban egy játék menete menete*/
                    else if (firstclick) {

                        /* a bal klikkre a harmadik változót a mezo_rajzol függvényben átírva bármelyik számod be"rajzolja", de struktúra híján még a zászlót és a számokat egymással felül lehet írni */
                        if (!lclick && event.button.x > 20 && event.button.x < ablak_x - 20 && event.button.y > 60 && event.button.y < ablak_y - 20) {

                            /* A tömb elemeire átkonvertálvan az egér koordinátáit*/
                            int tombx = (event.button.x-20)/LEVEL;
                            int tomby = (event.button.y-60)/LEVEL;

                            /* Első kattintásra generálódik a pálya, hogy ne lehessen röktön felrobbanni*/
                            if (!general){

                                tomb_feltolt(sizex, sizey ,tomb);
                                tomb_general(sizex, sizey, bomb, tomb, tombx, tomby);
                                general = true;
                                rajzolt_zaszlo = bomb;
                                /* Beállítja a kezdő időt*/
                                kezdet = clock();
                            }


                            if (!game_over){

                                        /* Alap eset, amikor elkezdünk játszani és nem fordítunk fel bombát */
                                        /* Felfordítja a megfelelő számot, ami a tömbben generálva lett */
                                        if (milyen(tombx, tomby, tomb) != Bomba){
                                                rajzol (renderer, mezok, ablak_x, ablak_y, event.button.x, event.button.y, LEVEL, tomb);
                                                lclick = true;
                                        }

                                        /* Bombára kattintottál...*/
                                        /* Nem engedi, hogy tovább játtsz és kiíja hogy game over*/
                                        if (milyen(tombx, tomby, tomb) == Bomba){

                                                felrobbant(renderer, mezok, sizex, sizey, ablak_x, ablak_y, LEVEL, tomb);
                                                game_over = true;
                                                lclick = true;


                                                /* Konzolba kiírja a veszés esetén kijött időd, de nem menti el fájlba*/
                                                time_t vege = clock();
                                                int mili = difftime(vege, kezdet) * 1000 / CLOCKS_PER_SEC;
                                                printf("%d seconds and %d miliseconds\n" , mili/1000, mili%1000);

                                                for (int i = 0; i < sizey; i++)
                                                    free(tomb[i]);

                                                free(tomb);
                                        }





                            }

                            /* Ha már meghaltál és kiírta a "Back to menu" szöveget, arra kattintva visszadob a menübe*/
                            else if (game_over) {
                                        if (event.button.x < ((ablak_x/2) + 50) && event.button.x > ((ablak_x/2) - 50) && event.button.y < ((ablak_y/2) + 30) && event.button.y > ((ablak_y/2) - 30)){

                                            menu(window, renderer);
                                            ablak_x = 520;
                                            ablak_y = 720;
                                            firstclick = false;

                                            game_over = false;
                                            general = false;


                                        }
                            }
                        }
                    }
                }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                /* A JOBB Egérgomb működése*/

                else if (event.button.button == SDL_BUTTON_RIGHT && !game_over) {

                       if (event.button.x > 20 && event.button.x < ablak_x - 20 && event.button.y > 60 && event.button.y < ablak_y - 20 && !rclick && tomb[(event.button.y-60)/LEVEL][(event.button.x-20)/LEVEL].leforditott) {

                            /* A tömb elemeire átkonvertálvan az egér koordinátáit*/
                            int tombx = (event.button.x-20)/LEVEL;
                            int tomby = (event.button.y-60)/LEVEL;


                            /* Ha nincs még zászló és le van fordítva a mező, akkor zászlót rak és számolja, hogy mennyi van lerakva*/
                            if (!tomb[tomby][tombx].zaszlos_e && rajzolt_zaszlo > 0){
                                mezo_rajzol(renderer, mezok, Zaszlo, event.button.x - ((event.button.x-20)%LEVEL), event.button.y - ((event.button.y-60)%LEVEL), LEVEL);
                                tomb[tomby][tombx].zaszlos_e = true;
                                rajzolt_zaszlo--;

                                /* Számolja hány bombán van zászló és, ha mindre kerül, akkor nyer a játékos*/
                                if (tomb[tomby][tombx].szam == -1)
                                        zaszlok++;

                                        /* NYERTÉL!!    A rekord időt elmentődik a pálya fájljába */
                                if (zaszlok == bomb){
                                    boxRGBA(renderer, (ablak_x/2) - 50, (ablak_y/2) - 30, (ablak_x/2) + 50, (ablak_y/2) + 30, 160, 160, 160, 255);
                                    stringRGBA(renderer, (ablak_x/2) - 35 , (ablak_y/2) - 20, "You win", 0, 0, 0, 255);
                                    stringRGBA(renderer,(ablak_x/2) - 46 , (ablak_y/2) + 8, "Back to menu", 0, 0, 0, 255);
                                    game_over = true;

                                    time_t vege = clock();

                                    int mili = difftime(vege, kezdet) * 1000 / CLOCKS_PER_SEC;
                                    printf("%d seconds and %d miliseconds\n" , mili/1000, mili%1000);

                                    /* Csak akkor menti el, ha az új idő jobb, mint az előző*/
                                    fileba_ment(LEVEL, mili);

                                        for (int i = 0; i < sizey; i++)
                                                free(tomb[i]);

                                        free(tomb);
                                }
                            }

                            /* Elveszi a zászlót*/
                            else {

                                if (tomb[tomby][tombx].szam == -1 && rajzolt_zaszlo > 0)
                                        zaszlok--;

                                if (tomb[tomby][tombx].zaszlos_e)
                                        rajzolt_zaszlo++;

                                mezo_rajzol(renderer, mezok, Leforditott, event.button.x - ((event.button.x-20)%LEVEL), event.button.y - ((event.button.y-60)%LEVEL), LEVEL);
                                tomb[tomby][tombx].zaszlos_e = false;

                            }

                       }

                    rclick = true;
                }
                break;


            /* egergomb elengedese */
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    lclick = false;
                }

                if (event.button.button == SDL_BUTTON_RIGHT) {
                    rclick = false;
                }
                break;

            /* ablak bezarasa */
            case SDL_QUIT:
                quit = true;
                break;
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}
