#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* renvoie la concaténation de dest et de string, la taille est stockée dans le pointeur taille */
char* ajouter_string(char* dest, int* taille, char* string);

/* renvoie la chaine associée à au moins une proposition de la liste l de taille n */
char* au_moins_une(char** l, int n);

/* renvoie la chaine associée à une seule une proposition de la liste l de taille n */
char* une_seule(char** l, int n);

/* renvoie la chaine associée à au plus une proposition de la liste l de taille n */
char* au_plus_une(char** l, int n);

/* renvoie la chaine associée à aucune des propositions de la liste l de taille n */
char* aucun(char** l, int n);

/* renvoie la chaine associée au et logique de toutes les propositions de la liste l de taille n */
char* et_liste(char** l, int n);

/* renvoie la chaine associée au ou logique de toutes les propositions de la liste l de taille n */
char* ou_liste(char** l, int n);

/* renvoie la chaine associée au et logique des propositions f1 et f2 */
char* et(char* f1, char* f2);

/* renvoie la chaine associée au ou logique des propositions f1 et f2 */
char* ou(char* f1, char* f2);

/* renvoie la chaine associée au l'implication logique des propositions expr1 vers expr2 */
char* implique(char* expr1, char* expr2);

/* renvoie la chaine associée au l'équivalence logique entre les propositions expr1 et expr2 */
char* equivalent(char* expr1, char* expr2);


/* renvoie la chaine associée la négation de expr */
char* non(char* expr);

#endif
