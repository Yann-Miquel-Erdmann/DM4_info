#include "taquin.h"

/*
 
 les cases et indices des tuiles vont de 1 à 9, le 9 représentant la case vide
 
 */

// TODO : bloquer les bord après qu'ils soient remplis
// TODO : bloquer le coin supérieur gauche quand il est bien placé
// TODO : faire en sorte que les tuiles ne puissent pas retourner en arrière i.e. pas annuler le move précédent
// TODO : implémenter des checkpoint: doit avoir fini une étape à partir d'un certain nombre de coups, permet à la fois d'avoir une solution plus rapide et une contrainte en plus
// TODO : trouver d'autres contraintes

/* renvoie la variable tu problème du taquin associée à l'index index_move, la valeur valeur_tuile
   la case case_n qui est directement  en négation si normal est à false */
char* variable_taquin(int index_move, int valeur_tuile, int case_n, bool normal){
    char buffer[50];
    int taille;
    if (normal){
        taille = sprintf(buffer, "Pos_%d_%d_%d", index_move, valeur_tuile, case_n)+1;
    }else{
        taille = sprintf(buffer, "~Pos_%d_%d_%d", index_move, valeur_tuile, case_n)+1;
    }
    char* string = malloc((taille)*sizeof(char));
    strcpy(string, buffer);
    return string;
}

/* renvoie un équivalent d'une variable de blocage d'une colone,
   i.e. toutes les variables de la colone et conjonction */
char* variable_bloc_colone(int taille_grille, int index_move, int index_colone){
    char** vars = malloc(taille_grille*sizeof(char*));
    for (int i = 0; i<taille_grille; i++){
        vars[i] =variable_taquin(index_move, i*taille_grille+ index_colone, i*taille_grille+ index_colone, true);
    }
    char* result = et_liste(vars, taille_grille);
    for (int i = 0; i<taille_grille; i++){
        free(vars[i]);
    }
    free(vars);
    return result;
}

/* renvoie un équivalent d'une variable de blocage d'une ligne,
   i.e. toutes les variables de la ligne et conjonction */
char* variable_bloc_ligne(int taille_grille, int index_move, int index_ligne){
    char** vars = malloc(taille_grille*sizeof(char*));
    for (int i = 0; i<taille_grille; i++){
        vars[i] = variable_taquin(index_move, (index_ligne-1)*taille_grille+1+i, (index_ligne-1)*taille_grille+1+i, true);
    }
    char* result = et_liste(vars, taille_grille);
    for (int i = 0; i<taille_grille; i++){
        free(vars[i]);
    }
    return result;
}

/* renvoie la conjonction de tous les mouvements possibles de la tuile de valeur valeur tuiles placée initialement
   sur la case case_n lors de l'index index_move dans une grille de taille taille_grille */
char* generate_move_tile(int taille_grille, int index_move, int case_n, int valeur_tuile){
    int enleve = 0;
    
    int total_tiles = taille_grille*taille_grille;
    
    char* mouvements[10];
    char* current_pos = variable_taquin(index_move, valeur_tuile, case_n, true);
    
    char* move[4];
    int enleve_move = 0;
    
    if ((case_n-1)%taille_grille == taille_grille-1){ // cas de la tuile à droite
        enleve += 2;
        enleve_move ++;
        
    }else{ // si elle n'est pas à droite
        move[0] = variable_taquin(index_move+1, valeur_tuile, case_n+1, true);
        char** vars = malloc(total_tiles*sizeof(char*));
        int less = 0;
        for (int i = 1; i <= total_tiles; i++){
            if (i == valeur_tuile){
                less = 1;
            }else{
                vars[i-less] = variable_taquin(index_move+1, i, case_n+1, false);
            }
        }
        vars[0] = variable_taquin(index_move, total_tiles, case_n+1, true);
        
        char* e1 = et_liste(vars, total_tiles);
        
        for (int i = 0; i<total_tiles; i++){
            free(vars[i]);
        }
        char* e2 = variable_taquin(index_move-1, valeur_tuile, case_n+1, false);
        
        char* condition1;
        if (index_move == 0){
            condition1 = e1;
        }else{
            condition1 = et(e2, e1);
            free(e1);
        }
        free(e2);
        char* condition2 = non(condition1);
        
        for (int i = 1; i <= total_tiles; i++){
            if (i == case_n+1){
                vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, true);
            }else{
                vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, false);
            }
        }
        char* instruction1 = et_liste(vars, total_tiles);
        for (int i = 0; i<total_tiles; i++){
            free(vars[i]);
        }
        free(vars);
        mouvements[0] = implique(condition1, instruction1);
        free(condition1);
        free(instruction1);
        char* instruction2 = variable_taquin(index_move+1, valeur_tuile, case_n+1, false);
        mouvements[1] = implique(condition2, instruction2);
        free(condition2);
        free(instruction2);
    }
    
    if ((case_n-1)%taille_grille == 0){ // cas de la tuile à gauche
        enleve += 2;
        enleve_move ++;
        
    }else{ // si elle n'est pas à gauche
        move[1-enleve_move] = variable_taquin(index_move+1, valeur_tuile, case_n-1, true);
        char** vars = malloc(total_tiles*sizeof(char*));
        int less = 0;
        for (int i = 1; i <= total_tiles; i++){
            if (i == valeur_tuile){
                less = 1;
            }else{
                vars[i-less] = variable_taquin(index_move+1, i, case_n-1, false);
            }
        }
        vars[0] = variable_taquin(index_move, total_tiles, case_n-1, true);
        
        char* e1 = et_liste(vars, total_tiles);
        
        for (int i = 0; i<total_tiles; i++){
            free(vars[i]);
        }
        char* e2 = variable_taquin(index_move-1, valeur_tuile, case_n-1, false);
        char* condition1;
        if (index_move == 0){
            condition1 = e1;
        }else{
            condition1 = et(e2, e1);
            free(e1);
        }
        free(e2);
        char* condition2 = non(condition1);
        
        for (int i = 1; i <= total_tiles; i++){
            if (i == case_n-1){
                vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, true);
            }else{
                vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, false);
            }
        }
        char* instruction1 = et_liste(vars, total_tiles);
        for (int i = 0; i<total_tiles; i++){
            free(vars[i]);
        }
        free(vars);
        mouvements[2-enleve] = implique(condition1, instruction1);
        free(condition1);
        free(instruction1);
        char* instruction2 = variable_taquin(index_move+1, valeur_tuile, case_n-1, false);
        mouvements[3-enleve] = implique(condition2, instruction2);
        free(condition2);
        free(instruction2);
    }
    
    if (case_n > taille_grille*(taille_grille-1)){ // cas de la tuile en bas
        enleve += 2;
        enleve_move ++;
        
    }else{ // si elle n'est pas en bas
        move[2-enleve_move] = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille, true);
        char** vars = malloc(total_tiles*sizeof(char*));
        int less = 0;
        for (int i = 1; i <= total_tiles; i++){
            if (i == valeur_tuile){
                less = 1;
            }else{
                vars[i-less] = variable_taquin(index_move+1, i, case_n+taille_grille, false);
            }
        }
        vars[0] = variable_taquin(index_move, total_tiles, case_n+taille_grille, true);
        
        char* e1 = et_liste(vars, total_tiles);
        
        for (int i = 0; i<total_tiles; i++){
            free(vars[i]);
        }
        char* e2 = variable_taquin(index_move-1, valeur_tuile, case_n+taille_grille, false);
        char* condition1;
        if (index_move == 0){
            condition1 = e1;
        }else{
            condition1 = et(e2, e1);
            free(e1);
        }
        free(e2);
        char* condition2 = non(condition1);
        
        for (int i = 1; i <= total_tiles; i++){
            if (i == case_n+taille_grille){
                vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, true);
            }else{
                vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, false);
            }
        }
        char* instruction1 = et_liste(vars, total_tiles);
        for (int i = 0; i<total_tiles; i++){
            free(vars[i]);
        }
        free(vars);
        mouvements[4-enleve] = implique(condition1, instruction1);
        free(condition1);
        free(instruction1);
        char* instruction2 = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille, false);
        mouvements[5-enleve] = implique(condition2, instruction2);
        free(condition2);
        free(instruction2);
    }
    
    if (case_n <= taille_grille){ // cas de la tuile est en haut
        enleve += 2;
        enleve_move ++;
        
    }else{// si elle n'est pas en haut
        move[3-enleve_move] = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille, true);
        char** vars = malloc(total_tiles*sizeof(char*));
        int less = 0;
        for (int i = 1; i <= total_tiles; i++){
            if (i == valeur_tuile){
                less = 1;
            }else{
                vars[i-less] = variable_taquin(index_move+1, i, case_n-taille_grille, false);
            }
        }
        vars[0] = variable_taquin(index_move, total_tiles, case_n-taille_grille, true);
        
        char* e1 = et_liste(vars, total_tiles);
        
        for (int i = 0; i<total_tiles; i++){
            free(vars[i]);
        }
        
        char* e2 = variable_taquin(index_move-1, valeur_tuile, case_n-taille_grille, false);
        char* condition1;
        if (index_move == 0){
            condition1 = e1;
        }else{
            condition1 = et(e2, e1);
            free(e1);
        }
        free(e2);
        char* condition2 = non(condition1);
        
        for (int i = 1; i <= total_tiles; i++){
            if (i == case_n-taille_grille){
                vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, true);
            }else{
                vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, false);
            }
        }
        char* instruction1 = et_liste(vars, total_tiles);
        for (int i = 0; i<total_tiles; i++){
            free(vars[i]);
        }
        free(vars);
        mouvements[6-enleve] = implique(condition1, instruction1);
        free(condition1);
        free(instruction1);
        char* instruction2 = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille, false);
        mouvements[7-enleve] = implique(condition2, instruction2);
        free(condition2);
        free(instruction2);
    }
    
    char* condition1 = ou_liste(move, 4-enleve_move);
    char* condition2 = non(condition1);
    
    char** vars = malloc((total_tiles+2)*sizeof(char*));
    for (int i= 1; i<=total_tiles; i++){
        if (i == case_n){
            vars[i-1] = variable_taquin(index_move+1, total_tiles, i, true);
        }else{
            vars[i-1] = variable_taquin(index_move+1, total_tiles, i, false);

        }
    }
    char* instruction1 = et_liste(vars, total_tiles);
    
    for (int i = 1; i<=total_tiles; i++){
        if (i == case_n){
            vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, true);
        }else{
            vars[i-1] = variable_taquin(index_move+1, valeur_tuile, i, false);
        }
    }
    
    char* instruction2 = et_liste(vars, 9);
    
    mouvements[8-enleve] = implique(condition1, instruction1);
    mouvements[9-enleve] = implique(condition2, instruction2);
    
    for(int i =  0; i< taille_grille; i++){
        free(vars[i]);
    }
    free(vars);
    free(instruction1);
    free(instruction2);
    free(condition1);
    free(condition2);

    char* pre_res = et_liste(mouvements, 10-enleve);
    
    for (int i = 0; i<10-enleve; i++){
        free(mouvements[i]);
    }
    
    char* result = implique(current_pos, pre_res);
    free(pre_res);
    
    return result;
}

/* renvoie la contriante de blocage de colonne sur une grille de taille taille_grille
   sur la colone index_colonne lors de l'index index_move */
char* generate_blocage_colonne(int taille_grille, int index_move, int index_colonne){
    char** vars = malloc((taille_grille*taille_grille*taille_grille+1)*sizeof(char*));
    int premiere = 0;
    for (int i = 1; i <= taille_grille; i++){
        for (int j = 1; j <= taille_grille*taille_grille; j++){
            vars[(i-1)*taille_grille*taille_grille+j-1] = variable_taquin(index_move, j, (i-1)*taille_grille+index_colonne, (i-1)*taille_grille+index_colonne == j);
        }
    }
    if (index_colonne != 1){
        premiere = 0;
        vars[taille_grille*taille_grille*taille_grille] = variable_bloc_colone(taille_grille, index_move+1, index_colonne-1);
    }
    char* condition1 = et_liste(vars, taille_grille*taille_grille*taille_grille-premiere);
    for (int i = 0; i< taille_grille*taille_grille*taille_grille-premiere; i++){
        free(vars[i]);
    }
    free(vars);
    char* instruction1 = variable_bloc_colone(taille_grille, index_move+1, index_colonne);
    char* condition2 = non(condition1);
    char* instruction2 = non(instruction1);
    
    char* pre_res1 = implique(condition1, instruction1);
    char* pre_res2 = implique(condition2, instruction2);
    
    char* result = et(pre_res1, pre_res2);
    free(condition1);
    free(instruction1);
    free(condition2);
    free(instruction2);
    free(pre_res1);
    free(pre_res2);
    
    return result;
}

/* renvoie la contriante de blocage de ligne sur une grille de taille taille_grille
   sur la logne index_ligne lors de l'index index_move */
char* generate_blocage_ligne(int taille_grille, int index_move, int index_ligne){
    char** vars = malloc((taille_grille*taille_grille*taille_grille)*sizeof(char*));
    for (int i = 1; i <= taille_grille; i++){
        for (int j = 1; j <= taille_grille*taille_grille; j++){
            vars[(i-1)*taille_grille*taille_grille+j-1] = variable_taquin(index_move, j, (index_ligne-1)*taille_grille+i, (index_ligne-1)*taille_grille+i == j);
        }
    }
    char* condition1 = et_liste(vars, taille_grille*taille_grille*taille_grille);
    for (int i = 0; i< taille_grille*taille_grille*taille_grille; i++){
        free(vars[i]);
    }
    
    for (int i = 1; i <= taille_grille; i++){
        for (int j = 1; j <= taille_grille*taille_grille; j++){
            vars[(i-1)*taille_grille*taille_grille+j-1] = variable_taquin(index_move+1, j, (index_ligne-1)*taille_grille+i, (index_ligne-1)*taille_grille+i == j);
        }
    }
    char* instruction1 = et_liste(vars, taille_grille*taille_grille*taille_grille);
    for (int i = 0; i< taille_grille*taille_grille*taille_grille; i++){
        free(vars[i]);
    }
    free(vars);
    char* result = implique(condition1, instruction1);
    free(condition1);
    free(instruction1);
    
    return result;
}

char* bloc_all_colones(int taille_grille, int index_move){
    char** vars = malloc((taille_grille-1)*sizeof(char*));
    for (int i = 0; i<taille_grille-1; i++){
        vars[i] = generate_blocage_colonne(taille_grille, index_move, i+1);
    }
    char* result = et_liste(vars, taille_grille-1);
    for (int i = 0; i<taille_grille-1; i++){
        free(vars[i]);
    }
    free(vars);
    return result;
}

/* renvoie le blocage pour toutes les lignes sur une grille de taille taille_grille sur le mouvement index_move */
char* bloc_all_lignes(int taille_grille, int index_move){
    char** vars = malloc((taille_grille-1)*sizeof(char*));
    for (int i = 0; i<taille_grille-1; i++){
        vars[i] = generate_blocage_ligne(taille_grille, index_move, i+1);
    }
    char* result = et_liste(vars, taille_grille-1);
    for (int i = 0; i<taille_grille-1; i++){
        free(vars[i]);
    }
    free(vars);
    return result;
}

/* renvoie la conjonction de tous les mouvements possibles sur une grille de taille taille_grille
   lors du mouvement d'index index_move */
char* generate_move(int taille_grille, int index_move){
    int taille = (taille_grille*taille_grille)*(taille_grille*taille_grille-1);
    int total_tiles = taille_grille*taille_grille;
    char** l = malloc(taille*sizeof(char*));
    for (int case_n = 1; case_n <= taille_grille*taille_grille; case_n++){
        for (int valeur_tuile = 1; valeur_tuile < taille_grille*taille_grille; valeur_tuile++){
            l[(case_n-1)*(taille_grille*taille_grille-1)+valeur_tuile-1] = generate_move_tile(taille_grille, index_move, case_n, valeur_tuile);
        }
    }
    
    char* instruction2 = et_liste(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    // si les pieces sont toutes bien placées
    char** vars = malloc((total_tiles*total_tiles)*sizeof(char*));
    for (int i = 1; i<=total_tiles; i++){
        for (int j = 1; j <= total_tiles; j++){
            vars[(i-1)*total_tiles+j-1] = variable_taquin(index_move, i, j, i==j);
        }
    }
    char* condition1 = et_liste(vars, total_tiles*total_tiles);
    
    for (int i = 0; i<total_tiles*total_tiles; i++){
        free(vars[i]);
    }
    
    // toutes tuiles placées alors ne pas bouger
    for (int i = 1; i<=total_tiles; i++){
        for (int j = 1; j <= total_tiles; j++){
            vars[(i-1)*total_tiles+j-1] = variable_taquin(index_move+1, i, j, i==j);
        }
    }
    char* instruction1 = et_liste(vars, total_tiles*total_tiles);
    for (int i = 0; i<total_tiles*total_tiles; i++){
        free(vars[i]);
    }
    free(vars);
    
    char* condition2 = non(condition1);
    //char* l2[4] = {bloc_all_lignes(taille_grille, index_move), bloc_all_colones(taille_grille, index_move), implique(condition1, instruction1), implique(condition2, instruction2)};
    char* l2[2] = {implique(condition1, instruction1), implique(condition2, instruction2)};

    char* result = et_liste(l2, 2);
    
    for (int i = 2; i<2; i++){
        free(l2[i]);
    }
    
    return result;
}

/* renvoie une obligation de la position position de var_len cases lors du mouvement d'index index_move */
char* generate_constraint_pos(int* position, int var_len, int index_move){
    int taille = var_len*var_len;
    char** l = malloc(taille*sizeof(char*));
    
    
    for (int i = 0; i< var_len; i++){
        for (int j = 1; j <= var_len; j++){
            l[(j-1)+var_len*i] = variable_taquin(index_move, j, i+1, position[i] == j);
        }
    }
    
    char* result = et_liste(l, taille);
    for (int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

int generate_solution(char* filename, int taille_grille, int* initial_position, int var_len){
    // vérifie si le solve se fair pour un taquin de 3 ou 4 cases de coté
    int var_len2;
    if (taille_grille == 3){
        var_len2 = 40;
    }else if (taille_grille == 4){
        var_len2 = 80;
    }else{
        printf("Ne peut pas générer de formule pour un taquin de %d cases de coté\n", taille_grille);
        exit(0);
    }
    
    // verifier validité position de base: éléments de 1 à la taille de la grille au carré moins 1
    // i.e. si la grille est de coté taille_grille avec nombres de 1 à var_len
    if (var_len != taille_grille*taille_grille){
        printf("Position initiale invalide 0\n");
        exit(1);
    }
    for (int i = 0; i< var_len; i++){
        bool valid = false;
        for (int j = 1; j <= var_len; j++){
            if (initial_position[i] == j){
                valid = true;
            }
        }
        if (!valid){
            printf("Position initiale invalide %d\n", i);
            exit(1);
        }
    }
    
    // générer la solution
    int taille = 3;
    char** l = malloc(taille*sizeof(char*));
    l[0] = generate_constraint_pos( initial_position, var_len, 0);
    
    char** variables = malloc(var_len2*sizeof(char*));

    for (int i = 0; i < var_len2; i++){
        variables[i] = generate_move(taille_grille, i);
    }
    l[1] = et_liste(variables, var_len2);
    for (int i = 0; i < var_len2; i++){
        free(variables[i]);
    }
    free(variables);
    
    int final_pos[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    l[2] = generate_constraint_pos(final_pos, var_len, var_len2);
    
    char* result = et_liste(l, 3);
    
    FILE* file = fopen(filename, "w");
    fprintf(file, "%s", result);
    fclose(file);
    
    for (int i = 0; i< 3; i++){
        free(l[i]);
    }
    free(l);
    int len = (int)strlen(result);
    free(result);
    return len;
}
