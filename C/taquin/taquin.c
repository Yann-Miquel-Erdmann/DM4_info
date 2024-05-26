#include "taquin.h"

char* variable_taquin(int index_move, int valeur_tuile, int case_n){
    char buffer[50];
    int taille = sprintf(buffer, "Pos_%d_%d_%d", index_move, valeur_tuile, case_n)+1;
    char* string = malloc(taille*sizeof(char));
    strcpy(string, buffer);
    return string;
}

char* generate_move(int taille_grille, int num_move, int case_n){
    int taille;
    char** l;
    switch (case_n) {
        case 1:
            taille = 2;
            l = malloc(2*sizeof(char*));
            break;
            
        case 2:
            taille = 3;
            l = malloc(3*sizeof(char*));
            break;
        
        case 3:
            taille = 2;
            l = malloc(2*sizeof(char*));
            break;
            
        case 4:
            taille = 3;
            l = malloc(3*sizeof(char*));
            break;
            
        case 5:
            taille = 4;
            l = malloc(4*sizeof(char*));
            break;
            
        case 6:
            taille = 3;
            l = malloc(3*sizeof(char*));
            break;
            
        case 7:
            taille = 2;
            l = malloc(2*sizeof(char*));
            break;
            
        case 8:
            taille = 3;
            l = malloc(3*sizeof(char*));
            break;
            
        case 9:
            taille = 2;
            l = malloc(2*sizeof(char*));
            break;
            
        default:
            break;
    }
    return "";
}
