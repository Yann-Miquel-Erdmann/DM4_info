#include "utils.h"

char* au_moins_une(char** l, int n){
    int taille = n+2;
    for (int i = 0; i<n; i++){
        taille += (int)strlen(l[i]);
    }
    printf("%d\n", taille);
    char* string = malloc(taille*sizeof(char));
    string[0] = '(';
    string[1] = '\0';
    for (int i = 0; i<n; i++){
        strcat(string, l[i]);
        if (i+1 != n){
            strcat(string, "|");
        }
    }
    strcat(string, ")");
    string[taille-1] = '\0';
    return string;
}

char* implique(char* expr1, char* expr2){
    int taille = (int)strlen(expr1) + (int)strlen(expr2) + 5; // (), le |, le ~ et le \0
    char* result = malloc(taille*sizeof(char));
    result[0] = '(';
    result[1] = '\0';
    strcat(result, expr2);
    strcat(result, "|~");
    strcat(result, expr1);
    strcat(result, ")");
    return result;
}

char* une_seule(char** l, int n){
    int taille = 2 + 2*n + n-1 + 2*n*(n-1) + 1; // parenthese debut et fin; les () ; les | ; les ~ et les & et le \0
    for (int i = 0; i<n; i++){
        taille += n*strlen(l[i]); // pour les variables qui vont apparaite n fois
    }
    char* string = malloc(taille*sizeof(char));
    string[0] = '(';
    string[1] = '\0';
    
    for (int i = 0; i<n; i++){
        strcat(string, "(");
        for (int j = 0; j<n; j++){
            if (i != j){
                strcat(string, "~");
            }
            strcat(string, l[j]);
            if (j+1 != n){
                strcat(string, "&");
            }
        }
        strcat(string, ")");
        if (i+1 != n){
            strcat(string, "|");
        }
    }
    strcat(string, ")");
    return string;
}

char* au_plus_une(char** l, int n){
    int taille = 2 + n + 2*(n-1)*n + 2*n + n + 1; // exterior (); |; &, ~; inner (); last | and ~; \0
    for (int i = 0; i<n; i++){
        taille += (n+1)*strlen(l[i]);
    }
    taille ++;
    char* string = malloc((taille+1)*sizeof(char));
    string[0] = '(';
    string[1] = '\0';
    
    for (int i = 0; i<n; i++){
        strcat(string, "(");
        for (int j = 0; j<n; j++){
            if (i != j){
                strcat(string, "~");
            }
            strcat(string, l[j]);
            if (j+1 != n){
                strcat(string, "&");
            }
        }
        strcat(string, ")");
        strcat(string, "|");
    }
    strcat(string, "~");
    strcat(string, "(");
    for (int j = 0; j<n; j++){
        strcat(string, l[j]);
        if (j+1 != n){
            strcat(string, "|");
        }
    }
    strcat(string, ")");
    strcat(string, ")");
    return string;
}

