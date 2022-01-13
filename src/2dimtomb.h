#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _2dimtomb_
#define _2dimtomb_

typedef struct Mezo {
    int szam;
    bool elso;
    bool leforditott;
    bool zaszlos_e;

}Mezo;

//legenerálja az egész két dimenziós tömböt
Mezo** tomb_lefoglal (int x , int y);

//feltölti a struktúra összes elemét
void tomb_feltolt (int x , int y, Mezo **tomb);

//legenerálja a bombákat és a számokat az első kattintáskor
void tomb_general (int x , int y, int bomba, Mezo **tomb, int elso_x, int elso_y);

#endif
