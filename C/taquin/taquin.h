#ifndef taquin_h
#define taquin_h

#include <stdio.h>

#include "../utils.h"

/* génère la totalité de la solution pour une grille de taille taille_grille avec la position de départ
   de longueur var_len et stocke le résultat dans le fichier de nom filename
   renvoie la taille de la chaine finale */
int generate_solution(char* filename, int taille_grille, int* initial_position, int var_len);

#endif
