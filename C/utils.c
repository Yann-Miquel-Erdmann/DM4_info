#include "utils.h"

char* ajouter_string(char* dest, int* taille, char* string){
    int len = (int)strlen(string);
    *taille += len;
    dest = realloc(dest, (*taille)*sizeof(char));
    strcat(dest, string);
    return dest;
}

char* au_moins_une(char** l, int n){
    char* string = malloc(sizeof(char));
    int taille = 1;
    string = ajouter_string(string, &taille, "(");
    for (int i = 0; i<n; i++){
        string =  ajouter_string(string, &taille, l[i]);
        if (i+1 != n){
            string = ajouter_string(string, &taille, "|");
        }
    }
    string = ajouter_string(string, &taille, ")");
    return string;
}

char* au_plus_une(char** l, int n){
    char* string = malloc(sizeof(char));
    int taille = 1;
    string[0] = '(';
    for (int i = 0; i<n; i++){
        taille ++;
        string = realloc(string, taille*sizeof(char));
        string[taille-1] = '(';
        for (int j = 0; j<n; j++){
            if (i != j){
                
            }else{
                
            }
        }
    }
    return string;
}

