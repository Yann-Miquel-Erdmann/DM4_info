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

#include "le_menteur.h"
#include "../utils.h"

// les trois affirmations du menteur
char** affirmations(void) {
    char** l = malloc(3 * sizeof(char*));
    l[0] = "(m_0&m_1)";
    l[1] = "(j_1_3|j_1_5|j_1_6)";
    l[2] = "(m_2&m_4)";
    return l;
}

int generate_solution_menteur(char* filename) {
    char** l = affirmations();
    char** jours_de_depart = malloc(7 * 8 * sizeof(char*));
    for (int i = 0; i < 7; i++) { // i est le jour de départ 
        char temp[100];
        
        char** jour0 = malloc(2 * sizeof(char*)); // soit le menteur ment le premier jour
        int taille = sprintf(temp, "(j_0_%d&~m_%d&%s)", i, i, l[0])+1;
        jour0[0] = malloc(taille * sizeof(char));
        strcpy(jour0[0], temp);
        // soit le menteur dit la vérité
        taille = sprintf(temp, "(j_0_%d&m_%d&~%s)", i, i, l[0])+1;
        jour0[1] = malloc(taille * sizeof(char));
        strcpy(jour0[1], temp);

        // soit le menteur ment le deuxième jour 
        char** jour1 = malloc(2 * sizeof(char*));
        taille = sprintf(temp, "(j_1_%d&~m_%d&%s)", (i + 1) % 7, (i + 1) % 7, l[1])+1;
        jour1[0] = malloc(taille * sizeof(char));
        strcpy(jour1[0], temp);
        // soit le menteur dit la vérité
        taille = sprintf(temp, "(j_1_%d&m_%d&~%s)", (i + 1) % 7, (i + 1) % 7, l[1])+1;
        jour1[1] = malloc(taille * sizeof(char));
        strcpy(jour1[1], temp);

        // soit le menteur ment le troisième jour
        char** jour2 = malloc(2 * sizeof(char*));
        taille = sprintf(temp, "(j_2_%d&~m_%d&%s)", (i + 2) % 7,(i + 2) % 7, l[2])+1;
        jour2[0] = malloc(taille * sizeof(char));
        strcpy(jour2[0], temp);
        // soit le menteur dit la vérité
        taille = sprintf(temp, "(j_2_%d&m_%d&~%s)", (i + 2) % 7,(i + 2) % 7, l[2])+1;
        jour2[1] = malloc(taille * sizeof(char));
        strcpy(jour2[1], temp);

        // fait la la conjonction de des formules des trois jours        
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int m = 0; m < 2; m++) {
                    taille = sprintf(temp, "(%s&%s&%s)", jour0[j], jour1[k], jour2[m])+1;
                    jours_de_depart[i * 8 + j * 4 + k * 2 + m] = malloc(taille * sizeof(char));
                    strcpy(jours_de_depart[i * 8 + j * 4 + k * 2 + m], temp);
                }
            }
            free(jour0[j]);
        }
        for (int j = 0; j<2; j++){
            free(jour1[j]);
            free(jour2[j]);
        }
        free(jour0);
        free(jour1);
        free(jour2);
        
    }
    free(l);
    

    char* jours = ou_liste(jours_de_depart, 7 * 8);
    for(int i = 0; i< 7*8; i++){
        free(jours_de_depart[i]);
    }
    free(jours_de_depart);

    // s'assure que le menteur ne dit la vérité qu'une seule fois
    char** verites = malloc(8* sizeof(char*));
    for (int i = 0; i<7; i++){
        char temp[10];
        int taille = sprintf(temp,"(~m_%d)", i)+1;
        verites[i] = malloc(taille*sizeof(char));
        strcpy(verites[i], temp);
    }
    char* unique_vrai = une_seule(verites,7) ;
    for (int i = 0; i<7; i++){
        free(verites[i]);
    }
    free(verites);
    

    // s'assure que les jours soient consécutifs
    char** jours_suivant = malloc(7*sizeof(char*));
    for (int i = 0; i<7; i++){
        char temp[50];
        int taille = sprintf(temp, "(j_0_%d&j_1_%d&j_2_%d)", i, (i+1)%7, (i+2)%7)+1;
        jours_suivant[i] = malloc(taille*sizeof(char));
        strcpy(jours_suivant[i], temp);
    }
    char* unique_jours_suivants = une_seule(jours_suivant, 7);
    for (int i = 0; i<7; i++){
        free(jours_suivant[i]);
    }
    free(jours_suivant);
    
    // s'assure que chacun des trois jours ne représente qu'un seul jour de la semaine
    char** unique_jour = malloc(3*sizeof(char*));
    char** jr = malloc(7*sizeof(char*));
    for (int i = 0; i<3; i++){
        char temp[10];
        
        for (int j = 0; j<7; j++){
            int taille = sprintf(temp, "j_%d_%d", i, j)+1;
            jr[j] = malloc(taille*sizeof(char));
            strcpy(jr[j], temp);

        }
        unique_jour[i] = une_seule(jr,7);
        for (int j = 0; j<7; j++){
            free(jr[j]);
        }
    }
    free(jr);
    
    char* unique_jours = et_liste(unique_jour,3);
    for (int i = 0; i<3; i++){
        free(unique_jour[i]);
    }
    free(unique_jour);

    char* unique1 = et(unique_jours_suivants, unique_jours);
    char* unique = et(unique1, unique_vrai);
    char* final = et(jours,unique);
    
    free(unique_jours_suivants);
    free(unique_jours);
    free(unique1);
    free(unique_vrai);
    free(jours);
    free(unique);
    
    FILE* file=  fopen(filename,"w");
    fprintf(file,"%s", final);
    int len = (int)strlen(final);
    fclose(file);
    free(final);
    return len;
}
