#include <stdio.h>
#include "utils.h"
#include "dames/n_dames.h"
#include "taquin/taquin.h"
#include "coloriage_carte.h"
#include "5_maisons/5_maisons.h"
#include "le_menteur.h"
#include "sudoku.h"

int main(void){
    int probleme = 0;
    char filename[100];
    printf("===== Générateur de problèmes pour le Satsolver =====\n\n");
    
    while (probleme > 5 || probleme < 1){
        printf("Choisis un problème à résoudre parmis les suivants:\n");
        printf("  1) Le menteur\n");
        printf("  2) Le coloriage de la carte de france\n");
        printf("  3) Le problème des 5 maisons\n");
        printf("  4) Le sudoku (grille requise)\n");
        printf("  5) Le taquin (configuration initiale requise) (pas résolvable)\n\n");
        
        printf("Choisis le numéro du problème: ");
        scanf("%d", &probleme);
    }
    
    printf("Choisis le fichier de sortie: ");
    scanf("%s", filename);
    
    char c = '\0';
    while (c != '\n'){
        scanf("%c", &c);
    }
    FILE* file = fopen(filename, "r");
    
    if (file != NULL){
        
        printf("Le fichier existe déjà, voulez vous l'écraser? (y/n) ");
        scanf("%c", &c);
        switch (c) {
            case 'y':
            case 'Y':
                printf("La fichier va être remplacé.\n");
                break;
            default:
                fclose(file);
                printf("Sortie du programme.\n");
                return 0;
                break;
        }
    }

    switch (probleme) {
        case 1:
            printf("Génération du problème du menteur en cours...\n");
            generate_solution_menteur(filename);
            break;
        case 2:
            printf("Génération du problème de la carte de france en cours...\n");
            generate_solution_carte(filename);
            break;
        case 3:
            printf("Génération du problème des cinq maisons en cours...\n");
            generate_solution_5_maisons(filename);
            break;
        case 4:
            printf("Grille 9x9\n");
            printf("Entrez les cases du sudoku (numéros 1-9 et 0 pour vide) séparées par des espaces:\n");
            int** position_départ_sudoku = malloc(9*sizeof(int*));
            for (int i = 0; i<9; i++){
                position_départ_sudoku[i] = malloc(9*sizeof(int));
                printf("Entrez la ligne %d: ", i+1);
                for (int j = 0; j<9; j++){
                    scanf("%d", &position_départ_sudoku[i][j]);
                }
            }
            printf("Génération du problème du sudoku en cours...\n");
            generate_solution_sudoku(filename, position_départ_sudoku);
            for(int i = 0; i<9; i++){
                free(position_départ_sudoku[i]);
            }
            free(position_départ_sudoku);
            break;
        case 5:
            printf("Plateau 3x3\n");
            printf("Entrez la position de départ (la case vide est le 9): ");
            int* position_départ_taquin = malloc(9*sizeof(int));
            for (int i = 0; i<9; i++){
                scanf("%d", &position_départ_taquin[i]);
            }
            printf("Génération du problème du taquin en cours...\n");
            generate_solution(3, position_départ_taquin, 9);
            free(position_départ_taquin);
            break;
            
        default:
            break;
    }
     
}
