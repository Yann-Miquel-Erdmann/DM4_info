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

char* une_seule(char** l, int n){
    int taille = n+2 + n*2 + n*(n+1);
    for (int i = 0; i<n; i++){
        taille += n*strlen(l[i]);
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
