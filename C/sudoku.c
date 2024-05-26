#include "utils.h"

/*
Variable: il y a l'entier k dans la case i j = i_j_k
Un seul par ligne
    pour toute ligne i
        pour tout entier k :
            un seul parmi {i_j_k (pout toute colone j)}

Un seul par colone
    pour toute colone j
        pour tout entier k :
            un seul parmi {i_j_k (pout toute ligne i)}

Un seul par carré
    pour tout carré c de coordonnées (i0, j0)
        pour tout entier k :
            un seul parmi {i_j_k (pout tout (i,j) E [i0, i0+2]x[j0, j0+2])}

*/

/*
1 3 2 4
4 2 3 1
3 4 1 2
2 1 4 3

1 _ 2 _
4 _ _ _
_ _ 1 _
2 _ 4 _

1 _ 

1 2 3 4
4 3 2 1
3 4 1 2
2 1 4 3


*/

char* initialisation_grille() {
    // char* string = "(0_0_0&0_1_1&0_2_2&0_3_3&1_0_3&1_1_2&1_2_1&1_3_0&2_0_2&2_1_3&2_2_0&2_3_1)\0";
    char* string = "(0_0_0)\0";
    return string;
}

char* lignes(int largeur, int hauteur) {
    char** contraintes = malloc(hauteur * sizeof(char*));
    for (int i = 0; i < hauteur; i++) {
        char** contrainte_ligne = malloc(largeur * sizeof(char*));
        for (int k = 0; k < largeur; k++) {
            char** contraintes_ligne_valeur = malloc(largeur * sizeof(char*));
            for (int j = 0; j < largeur; j++) {
                contraintes_ligne_valeur[j] = malloc(10 * sizeof(char));
                sprintf(contraintes_ligne_valeur[j], "%d_%d_%d", i, j, k);
                printf("%s\n", contraintes_ligne_valeur[j]);
            }
            contrainte_ligne[k] = une_seule(contraintes_ligne_valeur, largeur);
            for (int j = 0; j < largeur; j++) {
                free(contraintes_ligne_valeur[j]);
            }
            free(contraintes_ligne_valeur);
        }
        contraintes[i] = et(contrainte_ligne, largeur);
        for (int k = 0; k<largeur; k++){
            free(contrainte_ligne[k]);
        }
        free(contrainte_ligne);
    }

    return et(contraintes, hauteur);
}

char* colones(int largeur, int hauteur) {
    char** contraintes = malloc(largeur * sizeof(char*));
    for (int j = 0; j < largeur; j++) {
        char** contrainte_colone = malloc(hauteur * sizeof(char*));
        for (int k = 0; k < hauteur; k++) {
            char** contraintes_colonne_valeur = malloc(hauteur * sizeof(char*));
            for (int i = 0; i < hauteur; i++) {
                contraintes_colonne_valeur[i] = malloc(10 * sizeof(char));
                sprintf(contraintes_colonne_valeur[i], "%d_%d_%d", i, j, k);
                printf("%s\n", contraintes_colonne_valeur[i]);
            }
            contrainte_colone[k] = une_seule(contraintes_colonne_valeur, hauteur);
            for (int j = 0; j < largeur; j++) {
                free(contraintes_colonne_valeur[j]);
            }
            free(contraintes_colonne_valeur);
        }
        contraintes[j] = et(contrainte_colone, hauteur);
        for (int k = 0; k < largeur; k++) {
            free(contrainte_colone[k]);
        }
        free(contrainte_colone);
    }
    return et(contraintes, largeur);
}

char* cases(int largeur, int hauteur) {
    char** contraintes = malloc(largeur * hauteur * sizeof(char*));
    for (int i = 0; i < largeur; i++) {
        for (int j = 0; j < hauteur; j++) {
            char** contraintes_case = malloc(largeur * sizeof(char*));
            for (int k = 0; k < largeur; k++) {
                contraintes_case[k] = malloc(10 * sizeof(char));
                sprintf(contraintes_case[k], "%d_%d_%d", i, j, k);
            }
            contraintes[i * hauteur + j] = une_seule(contraintes_case, largeur);
            for (int k = 0; k < largeur; k++) {
                free(contraintes_case[k]);
            }
            free(contraintes_case);
        }
    }
    return et(contraintes, largeur * hauteur);
}

char* boites(int largeur, int hauteur, int largeur_boite, int hauteur_boite) {
    char** contraintes = malloc((largeur / largeur_boite) * (hauteur / hauteur_boite) * sizeof(char*));
    for (int i = 0; i < hauteur / hauteur_boite; i += 1) {
        printf("i = %d\n", i);
        for (int j = 0; j < largeur / largeur_boite; j += 1) {
            printf("j = %d\n", j);
            char** contraintes_boite = malloc(largeur * sizeof(char*));
            for (int k = 0; k < largeur; k++) {
                char** contraintes_boite_valeur = malloc(largeur_boite * hauteur_boite * sizeof(char*));
                for (int i1 = 0; i1 < hauteur_boite; i1++) {
                    for (int j1 = 0; j1 < largeur_boite; j1++) {
                        contraintes_boite_valeur[i1 * hauteur_boite + j1] = malloc(10 * sizeof(char));
                        sprintf(contraintes_boite_valeur[i1 * hauteur_boite + j1], "%d_%d_%d", i * hauteur_boite + i1, j * largeur_boite + j1, k);
                    }
                }
                contraintes_boite[k] = une_seule(contraintes_boite_valeur, largeur);
                for (int k = 0; k < largeur_boite*hauteur_boite; k++) {
                    free(contraintes_boite_valeur[k]);
                }
                free(contraintes_boite_valeur);
            }
            contraintes[i * hauteur_boite + j] = et(contraintes_boite, largeur);
            for (int k = 0; k < largeur; k++) {
                free(contraintes_boite[k]);
            }
            free(contraintes_boite);
        }
    }
    return et(contraintes, (largeur / largeur_boite) * (hauteur / hauteur_boite));
}

int main(int argc, char* argv[]) {
    int largeur = 2;
    int hauteur = 2;
    int largeur_boite = 2;
    int hauteur_boite = 1;
    char* string = initialisation_grille();
    char** contraintes = malloc(5 * sizeof(char*));
    contraintes[0] = string;
    contraintes[1] = lignes(largeur, hauteur);
    contraintes[2] = colones(largeur, hauteur);
    contraintes[3] = cases(largeur, hauteur);
    contraintes[4] = boites(largeur, hauteur, largeur_boite, hauteur_boite);
    char* contraintes_totales = et(contraintes, 5);
    // printf("%s\n", contraintes[3]);
    FILE* file = fopen("sudoku.txt", "w+");
    fprintf(file, "%s\n", contraintes_totales);
    fclose(file);
    for (int i = 1; i< 5; i++){
        free(contraintes[i]);
    }
    free(contraintes);
    free(contraintes_totales);
}
