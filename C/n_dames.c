#include "n_dames.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

char* variable(int i, int j){
    char buffer[50];
    int taille = sprintf(buffer, "X_%d_%d", i, j)+1;
    char* string = malloc(taille*sizeof(char));
    strcpy(string, buffer);
    return string;
}

char* contrainte_une_ligne(int i, int n){
    char** l = malloc(n*sizeof(char*));
    for (int k = 0; k<n; k++){
        l[k] = variable(i, k);
    }
    char* result = une_seule(l, n);
    for (int k = 0; k<n; k++){
        free(l[k]);
    }
    free(l);
    return result;
}

char* contrainte_toutes_lignes (int n){
    char** l = malloc(n*sizeof(char*));
    int taille = 0;
    for (int i = 0; i<n; i++){
        l[i] = contrainte_une_ligne(i, n);
        taille += strlen(l[i])+1; // ajout operateurs + parenthese de fin
    }
    taille += 2; // taille + 2 pour la parenthese de debut et le caractère nul
    char* result = malloc(taille*sizeof(char));
    result[0] = '(';
    result[1] = '\0';
    
    // concaténation des différents composants et free
    for (int i = 0; i<n; i++){
        strcat(result, l[i]);
        if (i+1 != n){
            strcat(result, "&");
        }
        free(l[i]);
    }
    free(l);
    
    result[taille-2] = ')';
    result[taille-1] = '\0';
    return result;
}

char* contrainte_une_colone(int i, int n){
    char** l = malloc(n*sizeof(char*));
    for (int k = 0; k<n; k++){
        l[k] = variable(k, i);
    }
    char* result = une_seule(l, n);
    for (int k = 0; k<n; k++){
        free(l[k]);
    }
    free(l);
    return result;
}

char* contrainte_toutes_colones (int n){
    char** l = malloc(n*sizeof(char*));
    int taille = 0;
    for (int i = 0; i<n; i++){
        l[i] = contrainte_une_colone(i, n);
        taille += strlen(l[i])+1; // ajout operateurs + parenthese de fin
    }
    taille += 2; // taille + 2 pour la parenthese de debut et le caractère nul
    char* result = malloc(taille*sizeof(char));
    result[0] = '(';
    result[1] = '\0';
    
    // concaténation des différents composants et free
    for (int i = 0; i<n; i++){
        strcat(result, l[i]);
        if (i+1 != n){
            strcat(result, "&");
        }
        free(l[i]);
    }
    free(l);
    
    result[taille-2] = ')';
    result[taille-1] = '\0';
    return result;
}

char* contrainte_une_diagonale_gauche(int i, int j, int n){
    int taille = n-i;
    if (i == 0){
        taille = j+1;
    }
    char** l = malloc(taille*sizeof(char*));
    for (int k = 0; k < taille; k++){
        l[k] = variable(i+k, j-k);
    }
    char* result = au_plus_une(l, taille);
    for (int k = 0; k < taille; k++){
        free(l[k]);
    }
    free(l);
    return result;
}

char* contrainte_une_diagonale_droite(int i, int j, int n){
    int taille = n-i;
    if (j > i){
        taille = n-j;
    }
    char** l = malloc(taille*sizeof(char*));
    for (int k = 0; k < taille; k++){
        l[k] = variable(i+k, j+k);
    }
    char* result = au_plus_une(l, taille);
    for (int k = 0; k < taille; k++){
        free(l[k]);
    }
    free(l);
    return result;
}

char* contrainte_toutes_diagonales (int n){
    char** l = malloc((2*(2*n-3))*sizeof(char*));  // n-1 cases + n-2 cases -> 2n-3 cases pour chaque coté
    printf("%d\n", 2*(2*n-3));
    int len_t = 2*n-3;
    int taille = 0;
    for (int i = 0; i<n-1; i++){
        l[i] = contrainte_une_diagonale_gauche(i, n-1, n);
        printf("%s, %d, %d\n", l[i], i, (int)strlen(l[i]));
        taille += strlen(l[i])+1; // ajout operateurs
        if (i != 0){
            l[n+i-2] = contrainte_une_diagonale_gauche(0, n-i-1, n);
            taille += strlen(l[n+i-2])+1; // ajout operateurs
            printf("%s, %d, %d\n", l[n+i-2], n+i-2, (int)strlen(l[n+i-2]));
        }
    }
    for (int i = 0; i<n-1; i++){
        l[len_t+i] = contrainte_une_diagonale_droite(i, 0, n);
        printf("%s, %d, %d\n", l[len_t+i], len_t+i, (int)strlen(l[len_t+i]));
        taille += strlen(l[len_t+i])+1; // ajout operateurs + parenthese de fin
        if (i != 0){
            l[len_t+n+i-2] = contrainte_une_diagonale_droite(0, i, n);
            taille += strlen(l[len_t+n+i-2])+1; // ajout operateurs + parenthese de fin
            printf("%s, %d, %d\n", l[len_t+n+i-2], len_t+n+i-2, (int)strlen(l[len_t+n+i-2]));
        }
    }
    printf("%d\n", taille - 2*(2*n-3));
    taille += 2; // taille + 2 pour la parenthese de debut et le caractère nul
    char* result = malloc(taille*sizeof(char));
    result[0] = '(';
    result[1] = '\0';
    
    // concaténation des différents composants et free
    for (int i = 0; i<2*len_t; i++){
        printf("%s, %d\n", l[i], i);
        strcat(result, l[i]);
        if (i+1 != 2*len_t){
            strcat(result, "&");
        }
        free(l[i]);
    }
    free(l);
    
    result[taille-2] = ')';
    result[taille-1] = '\0';
    return result;
}

void gen_formule_n_dames(int n, char* filename){
    char** l = malloc(3*sizeof(char*)); // 1 pour les lignes, 1 pour les colones, 1 pour les diagonales
    l[0] = contrainte_toutes_lignes(n);
    l[1] = contrainte_toutes_colones(n);
    l[2] = contrainte_toutes_diagonales(n);
    
    int taille = 0;
    for (int i = 0; i<3; i++){
        taille += strlen(l[i]);
    }
    char* result = malloc((taille+n+1)*sizeof(char));
    result[0] = '\0';
    printf("\n");
    for (int i = 0; i<3; i++){
        printf("%s\n", l[i]);
        strcat(result, l[i]);
        if (i != 2){
            strcat(result, "&");
            printf("added &\n");
        }
    }
    FILE* file = fopen(filename, "w");
    fprintf(file, "%s", result);
    printf("%s\n", result);
}
