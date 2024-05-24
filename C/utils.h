#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* ajouter_string(char* dest, int* taille, char* string) ;
char* au_moins_une(char** l, int n);
char* une_seule(char** l, int n);
char* au_plus_une(char** l, int n);


#endif
