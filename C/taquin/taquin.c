#include "taquin.h"

char* variable_taquin(int index_move, int valeur_tuile, int case_n){
    char buffer[50];
    int taille = sprintf(buffer, "Pos_%d_%d_%d", index_move, valeur_tuile, case_n)+1;
    char* string = malloc(taille*sizeof(char));
    strcpy(string, buffer);
    return string;
}

char* et_2_expr(char* expr1, char* expr2){
    int taille = (int)strlen(expr1) + (int)strlen(expr2) + 4; // (), & et \0
    char* result = malloc(taille*sizeof(char));
    result[0] = '(';
    result[1] = '\0';
    strcat(result, expr1);
    strcat(result, "&");
    strcat(result, expr2);
    strcat(result, ")");
    return result;
}

char* generate_move_tile(int taille_grille, int index_move, int case_n, int valeur_tuile){
    int taille;
    char** l;
    int var_len;
    char** variables;
    
    bool colone_droite = false;
    bool colone_gauche = false;
    bool ligne_haut = false;
    bool ligne_bas = false;
    
    if (case_n <= taille_grille){
        ligne_haut = true;
    }
    if (case_n > taille_grille*(taille_grille-1)){
        ligne_bas = true;
    }
    if ((case_n-1)%taille_grille == 0){
        colone_gauche = true;
    }
    if ((case_n-1)%taille_grille == taille_grille-1){
        colone_droite = true;
    }
    
    if (ligne_haut && colone_gauche){ // case 1
        var_len = 5;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n+1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille);
        variables[3] = variable_taquin(index_move, 0, case_n+1);
        variables[4] = variable_taquin(index_move, 0, case_n+taille_grille);
    }
    
    else if (ligne_haut && colone_droite){ // case 3
        var_len = 5;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n-1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille);
        variables[3] = variable_taquin(index_move, 0, case_n-1);
        variables[4] = variable_taquin(index_move, 0, case_n+taille_grille);
    }
    
    else if (ligne_bas && colone_gauche){ // case 7
        var_len = 5;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n+1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille);
        variables[3] = variable_taquin(index_move, 0, case_n+1);
        variables[4] = variable_taquin(index_move, 0, case_n-taille_grille);
    }
    
    else if (ligne_bas && colone_droite){ // case 9
        var_len = 5;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n-1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille);
        variables[3] = variable_taquin(index_move, 0, case_n-1);
        variables[4] = variable_taquin(index_move, 0, case_n-taille_grille);
    }
    
    else if (ligne_haut){ // case 2
        var_len = 7;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n-1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n+1);
        variables[3] = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille);
        variables[4] = variable_taquin(index_move, 0, case_n-1);
        variables[5] = variable_taquin(index_move, 0, case_n+1);
        variables[6] = variable_taquin(index_move, 0, case_n+taille_grille);
    }
    
    else if (ligne_bas){ // case 8
        var_len = 7;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n-1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n+1);
        variables[3] = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille);
        variables[4] = variable_taquin(index_move, 0, case_n-1);
        variables[5] = variable_taquin(index_move, 0, case_n+1);
        variables[6] = variable_taquin(index_move, 0, case_n-taille_grille);
    }
    
    else if (colone_gauche){ // case 4
        var_len = 7;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n+1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille);
        variables[3] = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille);
        variables[4] = variable_taquin(index_move, 0, case_n+1);
        variables[5] = variable_taquin(index_move, 0, case_n-taille_grille);
        variables[6] = variable_taquin(index_move, 0, case_n+taille_grille);
    }
    
    else if (colone_droite){ // case 6
        var_len = 7;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n-1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille);
        variables[3] = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille);
        variables[4] = variable_taquin(index_move, 0, case_n-1);
        variables[5] = variable_taquin(index_move, 0, case_n-taille_grille);
        variables[6] = variable_taquin(index_move, 0, case_n+taille_grille);
    }
    
    else{
        var_len = 9;
        variables = malloc(var_len*sizeof(char*));
        variables[0] = variable_taquin(index_move, valeur_tuile, case_n);
        variables[1] = variable_taquin(index_move+1, valeur_tuile, case_n-1);
        variables[2] = variable_taquin(index_move+1, valeur_tuile, case_n+1);
        variables[3] = variable_taquin(index_move+1, valeur_tuile, case_n-taille_grille);
        variables[4] = variable_taquin(index_move+1, valeur_tuile, case_n+taille_grille);
        variables[5] = variable_taquin(index_move, 0, case_n-1);
        variables[6] = variable_taquin(index_move, 0, case_n+1);
        variables[7] = variable_taquin(index_move, 0, case_n-taille_grille);
        variables[8] = variable_taquin(index_move, 0, case_n+taille_grille);
    }

    
    taille = (var_len-1)/2;
    l = malloc(taille*sizeof(char*));
    for (int i = 1; i<= taille; i++){
        l[i-1] = et_2_expr(implique(variables[0], variables[i]), variables[i+taille]);
        free(variables[i]);
        free(variables[i+taille]);
    }
    free(variables[0]);
    free(variables);
    
    char* result = ou(l, taille);
    for (int i =  0; i<taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* generate_constraint_tile(int taille_grille, int index_move){
    int taille = taille_grille*taille_grille;
    char** l = malloc(taille*sizeof(char*));
    
    for (int j = 1; j <= taille; j++){
        int var_len = taille_grille*taille_grille;
        char** variables = malloc(var_len*sizeof(char*));
        for (int i = 1; i <= var_len; i++){
            variables[i-1] = variable_taquin(index_move, i, j);
        }
        l[j-1] = une_seule(variables, var_len);
        for (int i = 0; i < var_len; i++){
            free(variables[i]);
        }
        free(variables);
    }
    char* result = et(l, taille);
    for (int i = 0; i<taille; i++){
        free(l[i]);
    }
    free(l);
    return result;
}

char* generate_move(int taille_grille, int index_move){
    int taille = (taille_grille*taille_grille)*(taille_grille*taille_grille-1)+1;
    char** l = malloc(taille*sizeof(char*));
    for (int case_n = 1; case_n <= taille_grille*taille_grille; case_n++){
        for (int valeur_tuile = 1; valeur_tuile < taille_grille*taille_grille; valeur_tuile++){
            l[(case_n-1)*(taille_grille*taille_grille-1)+valeur_tuile] = generate_move_tile(taille_grille, index_move, case_n, valeur_tuile);
        }
    }
    int var_len = taille_grille*taille_grille-1;
    char** variables = malloc(var_len*sizeof(char*));
    for (int i = 1; i<= var_len; i++){
        variables[i-1] = variable_taquin(index_move, i, i);
    }
    l[0] = et(variables, var_len);
    for (int i = 0; i<var_len; i++){
        free(variables[i]);
    }
    free(variables);
    
    char* var1 = generate_constraint_tile(taille_grille, index_move);
    
    char* var2 = ou(l, taille);
    
    char* result = et_2_expr(var2, var1);
    free(var1);
    free(var2);
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
        for (int j = 0; j < var_len; j++){
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
    char** variables = malloc(var_len*sizeof(char*));
    for (int i = 1; i<= var_len; i++){
        variables[i-1] = variable_taquin(0, initial_position[i-1], i);
    }
    l[0] = et(variables, var_len);
    for (int i = 0; i < var_len; i++){
        free(variables[i]);
    }
    free(variables);
    
    variables = malloc(var_len2*sizeof(char*));
    for (int i = 0; i < var_len2; i++){
        variables[i] = generate_move(taille_grille, i);
    }
    l[1] = et(variables, var_len2);
    for (int i = 0; i < var_len2; i++){
        free(variables[i]);
    }
    free(variables);
    
    variables = malloc(var_len*sizeof(char*));
    for (int i = 1; i<= var_len; i++){
        variables[i-1] = variable_taquin(var_len2+1, i, i);
    }
    l[2] = et(variables, var_len);
    for (int i = 0; i < var_len; i++){
        free(variables[i]);
    }
    free(variables);
    
    char* result = et(l, 3);
    return result;
}
