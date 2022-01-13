#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "debugmalloc.h"
#include "2dimtomb.h"

//legenerálja az egész két dimenziós tömböt az aknakereső pályához, bombákkal, számokkal együtt
Mezo** tomb_lefoglal (int x , int y){

    Mezo** p = (Mezo**) malloc(y*sizeof(Mezo*));

    for (int i = 0 ; i < y ; i++){
                p[i] = (Mezo*) malloc(x*sizeof(Mezo));
    }
    return p;
}

void tomb_feltolt (int x , int y, Mezo **tomb){

    for (int i = 0 ; i < y ; i++){
        for (int j = 0 ; j < x ; j++){
            tomb[i][j].szam = 0;
            tomb[i][j].elso = false;
            tomb[i][j].leforditott = true;
            tomb[i][j].zaszlos_e = false;
        }
    }
}

void tomb_general (int x , int y, int bomba, Mezo **tomb , int elso_x, int elso_y ){

    /*Az első kattintásra mindenképp nulla legyen és mellette is minden irányban */
    for (int a = elso_y-1 ; a <= elso_y + 1 ; a++){
            for (int b = elso_x-1 ; b <= elso_x + 1 ; b++){
                tomb[a][b].elso = true;
            }
    }

    /*random bomba generálás */
    /* ha ugyanazokat a koordinátákat generálja akkor visszalép (i--) hogy ne legyen kevesebb a bombaszám */
    for (int i = 0 ; i < bomba ; i++){
        int xr = rand()%x;
        int yr = rand()%y;
        if (tomb[yr][xr].szam != -1 && !tomb[yr][xr].elso)

            tomb[yr][xr].szam = -1;
        else i--;
    }

    /* Megszámolja hány bomba minden mező szomszédjában, átlóban is */
    for (int i = 0 ; i < y ; i++){
        for (int j = 0 ; j < x ; j++){

            if (i > 0 && j >0 && tomb[i-1][j-1].szam == -1 && tomb[i][j].szam != -1) tomb[i][j].szam ++;
            if (j >0 && tomb[i][j-1].szam == -1 && tomb[i][j].szam != -1) tomb[i][j].szam ++;
            if (i < (y-1) && j > 0 && tomb[i+1][j-1].szam == -1 && tomb[i][j].szam != -1) tomb[i][j].szam ++;

            if (i > 0 && tomb[i-1][j].szam == -1 && tomb[i][j].szam != -1) tomb[i][j].szam ++;
            if (i < (y-1) && tomb[i+1][j].szam == -1 && tomb[i][j].szam != -1) tomb[i][j].szam ++;

            if (i > 0 && j < (x-1) && tomb[i-1][j+1].szam == -1 && tomb[i][j].szam != -1) tomb[i][j].szam ++;
            if (j < (x-1) && tomb[i][j+1].szam == -1 && tomb[i][j].szam != -1) tomb[i][j].szam ++;
            if (i < (y-1) && j < (x-1) && tomb[i+1][j+1].szam == -1 && tomb[i][j].szam != -1) tomb[i][j].szam ++;
        }
    }

}
