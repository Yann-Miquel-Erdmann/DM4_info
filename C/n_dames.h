#ifndef n_dames_h
#define n_dames_h

#include <stdio.h>

char* variable(int i, int j);
char* contrainte_toutes_lignes (int n);
char* contrainte_toutes_colones (int n);
char* contrainte_toutes_diagonales (int n);
void gen_formule_n_dames(int n, char* filename);

#endif
