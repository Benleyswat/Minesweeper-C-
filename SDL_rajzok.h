#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "2dimtomb.h"

/* Az aknakereső elemei, a bombák, számok, olyan sorrendben, ahogy a képen,
 * igy a kapott egesz szamok megegyeznek a png-beli indexekkel*/
typedef enum Mezokep {
    Zaszlo, Rosszzaszlo, Bomba, Nullas, Egyes, Kettes, Harmas,
    Negyes, Otos, Hatos, Hetes, Nyolcas, Leforditott
} Mezokep;

enum { MERET = 200 };
enum { EASY = 40 };
enum { INTERMEDIATE = 30};
enum { HARD = 20 };

/* kirajzol egy aknakereső mezőt; a forrás a betöltött kép, a cél helyére rajzol.
  melyik képet, milyen koordinatakra: melyik, x, y.*/
void mezo_rajzol(SDL_Renderer *renderer, SDL_Texture *mezok, Mezokep melyik, int x, int y, int LEVEL);

void EASY_rajzol(SDL_Renderer *renderer, SDL_Texture *mezok);

void INTERMEDIATAE_rajzol(SDL_Renderer *renderer, SDL_Texture *mezok);

void HARD_rajzol(SDL_Renderer *renderer, SDL_Texture *mezok);

void menu(SDL_Window *window, SDL_Renderer *renderer);

Mezokep milyen (int x, int y, Mezo **tomb);

void rajzol (SDL_Renderer* renderer, SDL_Texture *mezok, int szeles, int magas, int x, int y, int LEVEL, Mezo **tomb);

void felrobbant (SDL_Renderer* renderer, SDL_Texture *mezok, int sizex, int sizey, int ablak_x, int ablak_y, int LEVEL, Mezo **tomb);


/* kulon fuggvenybe, hogy olvashatobb legyen */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);

