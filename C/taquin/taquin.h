#ifndef taquin_h
#define taquin_h

#include <stdio.h>
#include "../utils.h"

char* generate_move_tile(int taille_grille, int index_move, int case_n, int valeur_tuile);
char* generate_move(int taille_grille, int index_move);
char* generate_solution(int taille_grille, int* initial_position, int var_len);

#endif
