#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* ajouter_string(char* dest, int* taille, char* string) ;
char* au_moins_une(char** l, int n);
char* une_seule(char** l, int n);
char* au_plus_une(char** l, int n);
char* aucun(char** l, int n);
char* implique(char* expr1, char* expr2);

char* et(char** l, int n);  // le et logique de n formules
char* ou(char** l, int n);  // le et logique de n formules

#endif
