#include "utils.h"
#include <strings.h>

char* au_moins_une(char** l, int n) {
    int taille = n + 2;
    for (int i = 0; i < n; i++) {
        taille += (int)strlen(l[i]);
    }
    printf("%d\n", taille);
    char* string = malloc(taille * sizeof(char));
    string[0] = '(';
    string[1] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(string, l[i]);
        if (i + 1 != n) {
            strcat(string, "|");
        }
    }
    strcat(string, ")");
    string[taille - 1] = '\0';
    return string;
}

char* une_seule(char** l, int n) {
    int taille = 2 + 2 * n + n - 1 + 2 * n * (n - 1) + 1;  // parenthèse debut et fin; les () ; les | ; les ~ et les & et le \0
    for (int i = 0; i < n; i++) {
        // printf("%d\n", i);
        taille += n * strlen(l[i]);  // pour les variables qui vont apparaît n fois
    }
    char* string = malloc(taille * sizeof(char));
    string[0] = '(';
    string[1] = '\0';

    for (int i = 0; i < n; i++) {
        strcat(string, "(");
        for (int j = 0; j < n; j++) {
            if (i != j) {
                strcat(string, "~");
            }
            strcat(string, l[j]);
            if (j + 1 != n) {
                strcat(string, "&");
            }
        }
        strcat(string, ")");
        if (i + 1 != n) {
            strcat(string, "|");
        }
    }
    strcat(string, ")");
    return string;
}

char* au_plus_une(char** l, int n) {
    int taille = 2 + n + 2 * (n - 1) * n + 2 * n + n + 1;  // exterior (); |; &, ~; inner (); last | and ~; \0
    for (int i = 0; i < n; i++) {
        taille += (n + 1) * strlen(l[i]);
    }
    taille++;
    char* string = malloc((taille + 1) * sizeof(char));
    string[0] = '(';
    string[1] = '\0';

    for (int i = 0; i < n; i++) {
        strcat(string, "(");
        for (int j = 0; j < n; j++) {
            if (i != j) {
                strcat(string, "~");
            }
            strcat(string, l[j]);
            if (j + 1 != n) {
                strcat(string, "&");
            }
        }
        strcat(string, ")");
        strcat(string, "|");
    }
    strcat(string, "~");
    strcat(string, "(");
    for (int j = 0; j < n; j++) {
        strcat(string, l[j]);
        if (j + 1 != n) {
            strcat(string, "|");
        }
    }
    strcat(string, ")");
    strcat(string, ")");
    return string;
}

char* aucun(char** l, int n) {
    int taille = 2 + n + (n - 1) + 2;  // les () les ~ et les & et le \0
    for (int i = 0; i < n; i++) {
        taille += strlen(l[i]); 
    }
    printf("%d\n", taille);
    char* string = malloc(taille * sizeof(char));
    string[0] = '\0';

    strcat(string, "(");
    for (int i = 0; i < n; i++) {
        strcat(string, "~");
        strcat(string, l[i]);

        if (i + 1 != n) {
            strcat(string, "&");
        }
    }
    strcat(string, ")");
    return string;
}

char* et(char** l, int n) {
    int taille = 3 + n;  // les () et les & et le \0
    for (int i = 0; i < n; i++) {
        taille += strlen(l[i]);
    }
    char* string = malloc(taille * sizeof(char));
    string[0] = '(';
    string[1] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(string, l[i]);
        if (i + 1 != n) {
            strcat(string, "&");
        }
    }
    strcat(string, ")");
    return string;
}

char* ou(char** l, int n) {
    int taille = 3 + n;  // les () et les | et le \0
    for (int i = 0; i < n; i++) {
        taille += strlen(l[i]);
    }
    char* string = malloc(taille * sizeof(char));
    string[0] = '(';
    string[1] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(string, l[i]);
        if (i + 1 != n) {
            strcat(string, "|");
        }
    }
    strcat(string, ")");
    return string;
}
