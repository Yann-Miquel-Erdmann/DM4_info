#include <stdio.h>
#include <stdlib.h>

#include "../utils.h"
/*
régions = {
0:  Auvergne-Rhône-Alpes,
1:  Bourgogne-Franche-Comté,
2:  Bretagne,
3:  Centre-Val-de-Loire,
4:  Corse,
5:  Grand-Est,
6:  Hauts-de-France,
7:  Île-de-France,
8:  Normandie,
9: Nouvelle-Aquitaine,
10: Occitanie,
11: Pays-de-la-Loire,
12: Provence-Alpes-Côte d'Azur
}

Régions voisines = {
0: {1,3,9,10,12},
1: {0,3,5,7},
2: {8,11},
3: {0,1,7,8,9,11},
4: {},
5: {6,7,1},
6: {5,7,8},
7: {1,3,5,6,8},
8: {2,3,6,7,11},
9: {0,3,10,11},
10: {0,9,12},
11: {2,3,8,9},
12: {0,10}
}



Variable: la région i est de la couleur k = i_k

pour toute région i:
    un seul parmi {i_k pour toute couleur k}
    pour toute couleur k:
        i_k et aucun parmi {j_k pour tout voisin j de i}

*/

/* génère la liste d'adjacence des différents sommets du graphe
   représenté par les régions de la France */
void initialiser(int** voisins, int* voisin_tailles) {
    voisins[0] = malloc(5 * sizeof(int));
    voisins[0][0] = 1;
    voisins[0][1] = 3;
    voisins[0][2] = 9;
    voisins[0][3] = 10;
    voisins[0][4] = 12;
    voisin_tailles[0] = 5;

    voisins[1] = malloc(4 * sizeof(int));
    voisins[1][0] = 0;
    voisins[1][1] = 3;
    voisins[1][2] = 5;
    voisins[1][3] = 7;
    voisin_tailles[1] = 4;

    voisins[2] = malloc(2 * sizeof(int));
    voisins[2][0] = 8;
    voisins[2][1] = 11;
    voisin_tailles[2] = 2;

    voisins[3] = malloc(6 * sizeof(int));
    voisins[3][0] = 0;
    voisins[3][1] = 1;
    voisins[3][2] = 7;
    voisins[3][3] = 8;
    voisins[3][4] = 9;
    voisins[3][5] = 11;
    voisin_tailles[3] = 6;

    voisins[4] = malloc(0 * sizeof(int));
    voisin_tailles[4] = 0;

    voisins[5] = malloc(3 * sizeof(int));
    voisins[5][0] = 6;
    voisins[5][1] = 7;
    voisins[5][2] = 1;
    voisin_tailles[5] = 3;

    voisins[6] = malloc(3 * sizeof(int));
    voisins[6][0] = 5;
    voisins[6][1] = 7;
    voisins[6][2] = 8;
    voisin_tailles[6] = 3;

    voisins[7] = malloc(5 * sizeof(int));
    voisins[7][0] = 1;
    voisins[7][1] = 3;
    voisins[7][2] = 5;
    voisins[7][3] = 6;
    voisins[7][4] = 8;
    voisin_tailles[7] = 5;

    voisins[8] = malloc(5 * sizeof(int));
    voisins[8][0] = 2;
    voisins[8][1] = 3;
    voisins[8][2] = 6;
    voisins[8][3] = 7;
    voisins[8][4] = 11;
    voisin_tailles[8] = 5;

    voisins[9] = malloc(4 * sizeof(int));
    voisins[9][0] = 0;
    voisins[9][1] = 3;
    voisins[9][2] = 10;
    voisins[9][3] = 11;
    voisin_tailles[9] = 4;

    voisins[10] = malloc(3 * sizeof(int));
    voisins[10][0] = 0;
    voisins[10][1] = 9;
    voisins[10][2] = 12;
    voisin_tailles[10] = 3;

    voisins[11] = malloc(4 * sizeof(int));
    voisins[11][0] = 2;
    voisins[11][1] = 3;
    voisins[11][2] = 8;
    voisins[11][3] = 9;
    voisin_tailles[11] = 4;

    voisins[12] = malloc(2 * sizeof(int));
    voisins[12][0] = 0;
    voisins[12][1] = 10;
    voisin_tailles[12] = 2;
}

/* génère la solution au problème du coloriage de la carte
   i.e. colorier les différentes régions pour que
   deux adjacentes ne soient pas de la même couleur */
int generate_solution_carte(char* filename) {
    FILE* file = fopen(filename, "w");
    int n = 13;
    int nb_couleurs = 4;
    int** voisins = malloc(n * sizeof(int*));
    int* voisins_taille = malloc(n * sizeof(int));
    initialiser(voisins, voisins_taille);

    char** regions = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) { // itère sur les différentes régions
        
        char** couleurs = malloc(nb_couleurs * sizeof(char*));
        char** contrainte_couleurs_voisins = malloc((nb_couleurs + 1) * sizeof(char*));
        
        // génération des contraintes pour chacune des couleurs possibles
        for (int k = 0; k < nb_couleurs; k++) {
            char temp[20];
            int taille = sprintf(temp, "%d_%d", i, k)+1;
            couleurs[k] = malloc(taille * sizeof(char));
            strcpy(couleurs[k], temp);
            
            
            
            // s'assure qu'aucun des voisins n'a la même couleur que la région i 
            char** couleur_voisins = malloc(voisins_taille[i] * sizeof(char*));
            for (int j = 0; j < voisins_taille[i]; j++) {
                taille = sprintf(temp, "%d_%d", voisins[i][j], k)+1;
                couleur_voisins[j] = malloc(taille * sizeof(char));
                strcpy(couleur_voisins[j], temp);
            }
            
            char** contrainte_et = malloc(2 * sizeof(char*));
            if (voisins_taille[i] > 0) {
                contrainte_et[0] = aucun(couleur_voisins, voisins_taille[i]);
            } else {
                contrainte_et[0] = malloc(2*sizeof(char));
                strcpy(contrainte_et[0], "T");
            }
            
            for(int j = 0; j<voisins_taille[i]; j++){
                    free(couleur_voisins[j]);
            }
            free(couleur_voisins);
            
            contrainte_et[1] = malloc((strlen(couleurs[k])+1)*sizeof(char));
            strcpy(contrainte_et[1], couleurs[k]);

            contrainte_couleurs_voisins[k] = et_liste(contrainte_et, 2);
            for(int i = 0; i<2; i++){
                free(contrainte_et[i]);
            }
            free(contrainte_et);
            
        }
        
        // s’assure que chaque région n'a qu'une seule couleur associée
        char** contraintes_region = malloc(2 * sizeof(char*));
        contraintes_region[0] = une_seule(couleurs, nb_couleurs);
        contraintes_region[1] = ou_liste(contrainte_couleurs_voisins, nb_couleurs);
        for (int j = 0; j<nb_couleurs; j++){
            free(couleurs[j]);
            free(contrainte_couleurs_voisins[j]);
        }
        free(couleurs);
        free(contrainte_couleurs_voisins);

        regions[i] = et_liste(contraintes_region, 2);
        free(contraintes_region[0]);
        free(contraintes_region[1]);
        free(contraintes_region);
    }
    for (int i = 0; i< n; i++){
        free(voisins[i]);
    }
    free(voisins);
    free(voisins_taille);
    char* contraintes = et_liste(regions, n);
    for (int i = 0; i<n; i++){
        free(regions[i]);
    }
    free(regions);
    fprintf(file, "%s", contraintes);
    int len = (int)strlen(contraintes);
    free(contraintes);
    fclose(file);
    return len;
}

