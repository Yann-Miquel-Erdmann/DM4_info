/*
    variable m_i: le menteur ment le jour i iE[0,6]
    variable j_x_i: le jour x est le jour i xE[0,2] iE[0,6]
    affirmations:
        m_0&m1
        j_1_3|j_1_5|j_1_6
        m_2&m4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char** affirmations() {
    char** l = malloc(3 * sizeof(char*));
    l[0] = "(m_0&m_1)";
    l[1] = "(j_1_3|j_1_5|j_1_6)";
    l[2] = "(m_2&m_4)";
    return l;
}

void main(void) {
    char** l = affirmations();
    char** jours_de_depart = malloc(7 * 8 * sizeof(char*));
    for (int i = 0; i < 7; i++) {
        char** jour0 = malloc(2 * sizeof(char*));
        jour0[0] = malloc(50 * sizeof(char));
        jour0[1] = malloc(50 * sizeof(char));
        sprintf(jour0[0], "(j_0_%d&~m_%d&%s)", i, i, l[0]);
        sprintf(jour0[1], "(j_0_%d&m_%d&~%s)", i, i, l[0]);
        
        char** jour1 = malloc(2 * sizeof(char*));
        jour1[0] = malloc(50 * sizeof(char));
        jour1[1] = malloc(50 * sizeof(char));
        sprintf(jour1[0], "(j_1_%d&~m_%d&%s)", (i + 1) % 7, (i + 1) % 7, l[1]);
        sprintf(jour1[1], "(j_1_%d&m_%d&~%s)", (i + 1) % 7, (i + 1) % 7, l[1]);

        char** jour2 = malloc(2 * sizeof(char*));
        jour2[0] = malloc(50 * sizeof(char));
        jour2[1] = malloc(50 * sizeof(char));
        sprintf(jour2[0], "(j_2_%d&~m_%d&%s)", (i + 2) % 7,(i + 2) % 7, l[2]);
        sprintf(jour2[1], "(j_2_%d&m_%d&~%s)", (i + 2) % 7,(i + 2) % 7, l[2]);

        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int m = 0; m < 2; m++) {
                    jours_de_depart[i * 8 + j * 4 + k * 2 + m] = malloc(100 * sizeof(char));
                    sprintf(jours_de_depart[i * 8 + j * 4 + k * 2 + m], "(%s&%s&%s)", jour0[j], jour1[k], jour2[m]);
                }
            }
        }
    }
    
    char* jours = ou_liste(jours_de_depart, 7 * 8);
    char** verites = malloc(8* sizeof(char*));
    for (int i = 0; i<7; i++){
        verites[i] = malloc(8*sizeof(char*));
        sprintf(verites[i],"(~m_%d)", i);
    }
    char* unique_vrai = une_seule(verites,7) ;

    char** jours_suivant = malloc(7*sizeof(char*));
    for (int i = 0; i<7; i++){
        jours_suivant[i] = malloc(32*sizeof(char));
        sprintf(jours_suivant[i], "(j_0_%d&j_1_%d&j_2_%d)", i, (i+1)%7, (i+2)%7);
    }
    char* unique_jours_suivants = une_seule(jours_suivant, 7);

    char** unique_jour = malloc(3*sizeof(char*));
    for (int i = 0; i<3; i++){
        char** jr = malloc(7*sizeof(char*));
        for (int j = 0; j<7; j++){
            jr[j] = malloc(10*sizeof(char));
            sprintf(jr[j], "j_%d_%d", i, j);
        }
        unique_jour[i] = une_seule(jr,7);
    }
    char* unique_jours = et_liste(unique_jour,3);

    char* unique1 = et(unique_jours_suivants, unique_jours);
    char* unique = et(unique1, unique_vrai);
    char* final = et(jours,unique);
 
    FILE* file=  fopen("le_menteur.txt","w+");
    fprintf(file,"%s\n", final);
    fclose(file);
}