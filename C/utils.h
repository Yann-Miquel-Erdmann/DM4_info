#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ajouter_string(char* dest, int* taille, char* string);
char* au_moins_une(char** l, int n);
char* une_seule(char** l, int n);
char* au_plus_une(char** l, int n);
char* aucun(char** l, int n);

char* et_liste(char** l, int n);  // le et logique de n formules
char* ou_liste(char** l, int n);  // le et logique de n formules

char* et(char* f1, char* f2);  // le et logique de deux formules
char* ou(char* f1, char* f2);  // le ou logique de deux formules

#endif
