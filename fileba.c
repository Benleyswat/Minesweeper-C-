#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "debugmalloc.h"
#include "SDL_rajzok.h"
#include "fileba.h"

void fileba_ment(int LEVEL, int mili){

    if (LEVEL == EASY){

            FILE *fp;
            char legjobb[10];

            fp = fopen("Easy.txt", "rt");
            if (fp == NULL) {
                perror("File megnyitása sikertelen");
                return;
            }

            fgets(legjobb, 10, fp);

            fclose(fp);

            int legjobb_ido = atoi(legjobb);


            fp = fopen("Easy.txt", "wt");
            if (fp == NULL) {
                perror("File megnyitasa sikertelen");
                return;
            }

            if (legjobb_ido == 0)
                fprintf(fp, "%d\n", mili);

            else if (mili < legjobb_ido)
                fprintf(fp, "%d\n", mili);
            else
                fprintf(fp, "%d\n", legjobb_ido);

            fclose(fp);
    }

    else if (LEVEL == INTERMEDIATE){

            FILE *fp;
            char legjobb[10];

            fp = fopen("Intermediate.txt", "rt");
            if (fp == NULL) {
                perror("File megnyitasa sikertelen");
                return;
            }

            fgets(legjobb, 10, fp);

            fclose(fp);

            int legjobb_ido = atoi(legjobb);

            fp = fopen("Intermediate.txt", "wt");
            if (fp == NULL) {
                perror("File megnyitasa sikertelen");
                return;
            }

            if (legjobb_ido == 0)
                fprintf(fp, "%d\n", mili);

            else if (mili < legjobb_ido)
                fprintf(fp, "%d\n", mili);
            else
                fprintf(fp, "%d\n", legjobb_ido);

            fclose(fp);
    }

    else if (LEVEL == HARD){

            FILE *fp;
            char legjobb[10];

            fp = fopen("Hard.txt", "rt");
            if (fp == NULL) {
                perror("File megnyitasa sikertelen");
                return;
            }

            fgets(legjobb, 10, fp);

            fclose(fp);

            int legjobb_ido = atoi(legjobb);

            fp = fopen("Hard.txt", "wt");
            if (fp == NULL) {
                perror("File megnyitasa sikertelen");
                return;
            }

            if (legjobb_ido == 0)
                fprintf(fp, "%d\n", mili);

            else if (mili < legjobb_ido)
                fprintf(fp, "%d\n", mili);
            else
                fprintf(fp, "%d\n", legjobb_ido);


            fclose(fp);
    }

    else
        printf("No such file in directory.\n");
}
