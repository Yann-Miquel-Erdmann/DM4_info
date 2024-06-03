#include "taquin.h"

/*
 
 les cases et indices des tuiles vont de 1 à 9, le 9 représentant la case vide
 
 */

// TODO : bloquer les bord après qu'ils soient remplis
// TODO : bloquer le coin supérieur gauche quand il est bien placé
// TODO : faire en sorte que les tuiles ne puissent pas retourner en arrière i.e. pas annuler le move précédent
// TODO : implémenter des checkpoint: doit avoir fini une étape à partir d'un certain nombre de coups, permet à la fois d'avoir une solution plus rapide et une contrainte en plus
// TODO : trouver d'autres contraintes

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

char* variable_bloc_colone(int taille_grille, int index_move, int index_colone){
    char* vars[3] = {variable_taquin(index_move, index_colone, index_colone, true), variable_taquin(index_move, taille_grille+index_colone, taille_grille+index_colone, true), variable_taquin(index_move, 2*taille_grille+index_colone, 2*taille_grille+index_colone, true)};
    
    char* result = et_liste(vars, 3);
    for (int i = 0; i<3; i++){
        free(vars[i]);
    }
    return result;
}

char* variable_bloc_ligne(int taille_grille, int index_move, int index_ligne){
    char* vars[3] = {variable_taquin(index_move, (index_ligne-1)*taille_grille+1, (index_ligne-1)*taille_grille+1, true), variable_taquin(index_move, (index_ligne-1)*taille_grille+2, (index_ligne-1)*taille_grille+2, true), variable_taquin(index_move, (index_ligne-1)*taille_grille+3, (index_ligne-1)*taille_grille+3, true)};
    
    char* result = et_liste(vars, 3);
    for (int i = 0; i<3; i++){
        free(vars[i]);
    }
    return result;
}

char* generate_move_tile(int taille_grille, int index_move, int case_n, int valeur_tuile){
    int enleve = 0;
    
    int total_tiles = taille_grille*taille_grille;
    
    char** mouvements = malloc(10*sizeof(char*));
    char* current_pos = variable_taquin(index_move, valeur_tuile, case_n, true);
    
    char* move[4];
    int enleve_move = 0;
    
    if ((case_n-1)%taille_grille == taille_grille-1){ // a droite
        enleve += 2;
        enleve_move ++;
    }else{
        move[0] = variable_taquin(index_move+1, valeur_tuile, case_n+1, true);
        char* vars[total_tiles];
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
        char* condition2 = not(condition1);
        
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
        mouvements[0] = implique(condition1, instruction1);
        free(condition1);
        free(instruction1);
        char* instruction2 = variable_taquin(index_move+1, valeur_tuile, case_n+1, false);
        mouvements[1] = implique(condition2, instruction2);
        free(condition2);
        free(instruction2);
    }
    
    if ((case_n-1)%taille_grille == 0){ // a gauche
        enleve += 2;
        enleve_move ++;
    }else{
        move[1-enleve_move] = variable_taquin(index_move+1, valeur_tuile, case_n-1, true);
        char* vars[total_tiles];
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
        char* condition2 = not(condition1);
        
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
        mouvements[2-enleve] = implique(condition1, instruction1);
        free(condition1);
        free(instruction1);
        char* instruction2 = variable_taquin(index_move+1, valeur_tuile, case_n-1, false);
        mouvements[3-enleve] = implique(condition2, instruction2);
        free(condition2);
        free(instruction2);
    }
    
    if (case_n > taille_grille*(taille_grille-1)){ // en bas
        enleve += 2;
        enleve_move ++;
    }else{
        move[2-enleve_move] = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille, true);
        char* vars[total_tiles];
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
        char* condition2 = not(condition1);
        
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
        mouvements[4-enleve] = implique(condition1, instruction1);
        free(condition1);
        free(instruction1);
        char* instruction2 = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille, false);
        mouvements[5-enleve] = implique(condition2, instruction2);
        free(condition2);
        free(instruction2);
    }
    
    if (case_n <= taille_grille){ // en haut
        enleve += 2;
        enleve_move ++;
    }else{
        move[3-enleve_move] = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille, true);
        char* vars[total_tiles];
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
        char* condition2 = not(condition1);
        
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
        mouvements[6-enleve] = implique(condition1, instruction1);
        free(condition1);
        free(instruction1);
        char* instruction2 = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille, false);
        mouvements[7-enleve] = implique(condition2, instruction2);
        free(condition2);
        free(instruction2);
    }
    
    char* condition1 = ou_liste(move, 4-enleve_move);
    char* condition2 = not(condition1);
    
    char* vars[total_tiles+2];
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
    free(instruction1);
    free(instruction2);
    free(condition1);
    free(condition2);

    char* pre_res = et_liste(mouvements, 10-enleve);
    
    for (int i = 0; i<10-enleve; i++){
        free(mouvements[i]);
    }
    free(mouvements);
    
    char* result = implique(current_pos, pre_res);
    free(pre_res);
    
    return result;
}

char* generate_blocage_colone(int taille_grille, int index_move, int index_colone){
    char* vars[taille_grille*taille_grille*taille_grille+1];
    int premiere = 0;
    for (int i = 1; i <= taille_grille; i++){
        for (int j = 1; j <= taille_grille*taille_grille; j++){
            vars[(i-1)*taille_grille*taille_grille+j-1] = variable_taquin(index_move, j, (i-1)*taille_grille+index_colone, (i-1)*taille_grille+index_colone == j);
        }
    }
    if (index_colone != 1){
        premiere = 0;
        vars[taille_grille*taille_grille*taille_grille] = variable_bloc_colone(taille_grille, index_move+1, index_colone-1);
    }
    char* condition1 = et_liste(vars, taille_grille*taille_grille*taille_grille-premiere);
    for (int i = 0; i< taille_grille*taille_grille*taille_grille-premiere; i++){
        free(vars[i]);
    }
    char* instruction1 = variable_bloc_colone(taille_grille, index_move+1, index_colone);
    char* condition2 = not(condition1);
    char* instruction2 = not(instruction1);
    
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

char* generate_blocage_ligne(int taille_grille, int index_move, int index_ligne){
    char* vars[taille_grille*taille_grille*taille_grille];
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
    
    char* result = implique(condition1, instruction1);
    free(condition1);
    free(instruction1);
    
    return result;
}

char* bloc_all_colones(int taille_grille, int index_move){
    char* vars[taille_grille-1];
    for (int i = 0; i<taille_grille-1; i++){
        vars[i] = generate_blocage_colone(taille_grille, index_move, i+1);
    }
    char* result = et_liste(vars, taille_grille-1);
    for (int i = 0; i<taille_grille-1; i++){
        free(vars[i]);
    }
    return result;
}

char* bloc_all_lignes(int taille_grille, int index_move){
    char* vars[taille_grille-1];
    for (int i = 0; i<taille_grille-1; i++){
        vars[i] = generate_blocage_ligne(taille_grille, index_move, i+1);
    }
    char* result = et_liste(vars, taille_grille-1);
    for (int i = 0; i<taille_grille-1; i++){
        free(vars[i]);
    }
    return result;
}

char* generate_constraint_tile(int taille_grille, int index_move, int valeur_tuile){
    char* vars[taille_grille*taille_grille];
    for (int i = 1; i<= taille_grille*taille_grille; i++){
        vars[i-1] = variable_taquin(index_move, valeur_tuile, i, true);
    }
    char* result = une_seule(vars, taille_grille*taille_grille);
    for (int i = 0; i< taille_grille*taille_grille; i++){
        free(vars[i]);
    }
    return result;
}

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
    char* vars[total_tiles*total_tiles];
    for (int i = 1; i<=total_tiles; i++){
        for (int j = 1; j <= total_tiles; j++){
            vars[(i-1)*total_tiles+j-1] = variable_taquin(index_move, i, j, i==j);
        }
    }
    char* condition1 = et_liste(vars, total_tiles*total_tiles);
    
    for (int i = 0; i<total_tiles*total_tiles; i++){
        free(vars[i]);
    }
    
    for (int i = 1; i<=total_tiles; i++){
        for (int j = 1; j <= total_tiles; j++){
            vars[(i-1)*total_tiles+j-1] = variable_taquin(index_move+1, i, j, i==j);
        }
    }
    char* instruction1 = et_liste(vars, total_tiles*total_tiles);
    for (int i = 0; i<total_tiles*total_tiles; i++){
        free(vars[i]);
    }

    char* condition2 = not(condition1);
    //char* l2[4] = {bloc_all_lignes(taille_grille, index_move), bloc_all_colones(taille_grille, index_move), implique(condition1, instruction1), implique(condition2, instruction2)};
    char* l2[4] = {"T", "T", implique(condition1, instruction1), implique(condition2, instruction2)};

    char* result = et_liste(l2, 4);
    
    for (int i = 2; i<4; i++){
        free(l2[i]);
    }
    
    return result;
}

char* generate_constraint_pos(int taille_grille, int* position, int var_len, int index_move){
    int taille = var_len*var_len;
    char** l = malloc(taille*sizeof(char*));
    
    
    for (int i = 0; i< var_len; i++){
        for (int j = 1; j <= var_len; j++){
            l[(j-1)+var_len*i] = variable_taquin(index_move, j, i+1, true);
            if (position[i] != j){
                char* var = malloc((strlen(l[(j-1)+var_len*i])+2)*sizeof(char));
                var[0] = '~';
                var[1] = '\0';
                strcat(var, l[(j-1)+var_len*i]);
                free(l[(j-1)+var_len*i]);
                l[(j-1)+var_len*i] = var;
            }
        }
    }
    
    char* result = et_liste(l, taille);
    for (int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* generate_solution(int taille_grille, int* initial_position, int var_len){
    // vérifie si le solve se fair pour un taquin de 3 ou 4 cases de coté
    int var_len2;
    if (taille_grille == 3){
        var_len2 = 40;
    }else if (taille_grille == 4){
        var_len2 = 80;
    }else{
        printf("Ne peut pas générer de formule pour un taquin de %d cases de coté\n", taille_grille);
        return "";
    }
    
    // verifier validité position de base: éléments de 1 à la taille de la grille au carré moins 1
    // i.e. si la grille est de coté 3, de 1 à 8
    if (var_len != taille_grille*taille_grille){
        printf("Position initiale invalide 0\n");
        return "";
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
            return "";
        }
    }
    
    // générer la solution
    int taille = 3;
    char** l = malloc(taille*sizeof(char*));
    l[0] = generate_constraint_pos(taille_grille, initial_position, var_len, 0);
    
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
    l[2] = generate_constraint_pos(taille_grille, final_pos, var_len, var_len2);
    
    char* result = et_liste(l, 3);
    
    for (int i = 0; i< 3; i++){
        free(l[i]);
    }
    free(l);
    return result;
}
