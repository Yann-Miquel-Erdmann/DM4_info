#include "5_maisons.h"

char* variables_maisons(int type, int valeur, int colone){
    char buffer[50];
    char* type_s;
    char* valeur_s;
    char* liste0[5] = {"rouge", "bleu", "vert", "jaune", "blanche"};
    char* liste1[5] = {"escalade", "danse", "karaté", "basket", "vélo"};
    char* liste2[5] = {"eau", "lait", "yop", "thé", "café"};
    char* liste3[5] = {"allemand", "suédois", "norvégien", "danois", "anglais"};
    char* liste4[5] = {"chat", "chien", "poisson", "cheval", "oiseau"};
    switch (type) {
        case 0:
            type_s = "couleur";
            valeur_s = liste0[valeur];
            break;
        case 1:
            type_s = "sport";
            valeur_s = liste1[valeur];
            break;
        case 2:
            type_s = "boisson";
            valeur_s = liste2[valeur];
            break;
        case 3:
            type_s = "nationalité";
            valeur_s = liste3[valeur];
            break;
        case 4:
            type_s = "animal";
            valeur_s = liste4[valeur];
            break;
        default:
            type_s = "";
            valeur_s = "";
            break;
    }
    int taille = sprintf(buffer, "tab_%s_%s_%d", type_s, valeur_s, colone)+1;
    char* string = malloc((taille+1)*sizeof(char));
    strcpy(string, buffer);
    return string;
}

/*
 couleur:
 - rouge
 - bleu
 - vert
 - jaune
 - blanche
 
 sport:
 - escalade
 - danse
 - karaté
 - basket
 - vélo
 
 boisson:
 - eau
 - lait
 - yop
 - thé
 - café
 
 nationalité:
 - allemand
 - suédois
 - norvégien
 - danois
 - anglais
 
 animal:
 - chat
 - chien
 - poisson
 - cheval
 - oiseau
 */

char* contrainte1(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(0, 0, i); // rouge
        char* expr2 = variables_maisons(3, 4, i); // anglais
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte2(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(4, 1, i); // chien
        char* expr2 = variables_maisons(3, 1, i); // suédois
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte3(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(2, 3, i); // thé
        char* expr2 = variables_maisons(3, 3, i); // danois
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte4(void){
    int taille = 4;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(0, 2, i); // vert
        char* expr2 = variables_maisons(0, 4, i+1); // blanche
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte5(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(0, 2, i); // vert
        char* expr2 = variables_maisons(2, 4, i); // café
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte6(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(1, 4, i); // vélo
        char* expr2 = variables_maisons(4, 4, i); // oiseau
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte7(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(0, 3, i); // jaune
        char* expr2 = variables_maisons(1, 1, i); // danse
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte8(void){
    return variables_maisons(2, 1, 2); // lait
}

char* contrainte9(void){
    return variables_maisons(3, 2, 0); // norvégien
}

char* contrainte10(void){
    int taille = 8;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 0, i); // escalade
        char* expr2 = variables_maisons(4, 0, i+1); // chat
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 0, i+1); // escalade
        char* expr2 = variables_maisons(4, 0, i); // chat
        l[taille/2+i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte11(void){
    int taille = 8;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 1, i); // danse
        char* expr2 = variables_maisons(4, 3, i+1); // cheval
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 1, i+1); // danse
        char* expr2 = variables_maisons(4, 3, i); // cheval
        l[taille/2+i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte12(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(1, 3, i); // basket
        char* expr2 = variables_maisons(2, 2, i); // yop
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte13(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(1, 2, i); // karaté
        char* expr2 = variables_maisons(3, 0, i); // allemand
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte14(void){
    int taille = 8;
    char** l = malloc(taille*sizeof(char*));
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(0, 1, i); // bleu
        char* expr2 = variables_maisons(3, 2, i+1); // norvégien
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(0, 1, i+1); // bleu
        char* expr2 = variables_maisons(3, 2, i); // norvégien
        l[taille/2+i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte15(void){
    int taille = 8;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 0, i); // escalade
        char* expr2 = variables_maisons(2, 0, i+1); // eau
        l[i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 0, i+1); // escalade
        char* expr2 = variables_maisons(2, 0, i); // eau
        l[taille/2+i] = et_2_expr(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

char* contrainte_ligne(int n){
    char** l = malloc(5*sizeof(char*));
    for (int i = 0; i<5; i++){
        char* variables[5] = {variables_maisons(n, 0, i),variables_maisons(n, 1, i),variables_maisons(n, 2, i),variables_maisons(n, 3, i),variables_maisons(n, 4, i)};
        l[i] = une_seule(variables, 5);
        for (int j = 0; j < 5; j++){
            free(variables[j]);
        }
    }
    char* result = et(l, 5);
    for (int i = 0; i< 5; i++){
        free(l[i]);
    }
    free(l);
    return result;
}

char* contrainte_placement(int n){
    char** l = malloc(5*sizeof(char*));
    for (int i = 0; i<5; i++){
        char* variables[5] = {variables_maisons(n, i, 0),variables_maisons(n, i, 1),variables_maisons(n, i, 2),variables_maisons(n, i, 3),variables_maisons(n, i, 4)};
        l[i] = une_seule(variables, 5);
        for (int j = 0; j < 5; j++){
            free(variables[j]);
        }
    }
    char* result = et(l, 5);
    for (int i = 0; i< 5; i++){
        free(l[i]);
    }
    free(l);
    return result;
}

char* generate_solution_5_maisons(void){
    char** variables = malloc(5*sizeof(char*));
    for (int i = 0; i<5; i++){
        variables[i] = contrainte_ligne(i);
    }
    char* expr1 = et(variables, 5);
    
    for (int i = 0; i<5; i++){
        free(variables[i]);
        variables[i] = contrainte_placement(i);
    }
    char* expr2 = et(variables, 5);
    for (int i = 0; i<5; i++){
        free(variables[i]);
    }
    free(variables);
    
    char* l[17] = {
        contrainte1(),
        contrainte2(),
        contrainte3(),
        contrainte4(),
        contrainte5(),
        contrainte6(),
        contrainte7(),
        contrainte8(),
        contrainte9(),
        contrainte10(),
        contrainte11(),
        contrainte12(),
        contrainte13(),
        contrainte14(),
        contrainte15(),
        expr1,
        expr2
    };
    
    char* result = et(l, 17);
    
    for (int i = 0; i< 17; i++){
        free(l[i]);
    }
    
    return result;
}
