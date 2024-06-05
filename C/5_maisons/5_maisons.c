#include "5_maisons.h"


/* Liste des catégories et des valeurs, triées selon celles utilisées pour la génération des variables
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

/* renvoie la variable du satsolver qui a pour catégorie l'entier type compris entre 0 et 4
   comme valeur l'entier valeur compris entre 0 et 4 et qui se trouve dans la colonne colone comprise entre 0 et 4
   la chaîne de caractère renvoyée doit être free */

char* variables_maisons(int type, int valeur, int colonne){
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
    int taille = sprintf(buffer, "tab_%s_%s_%d", type_s, valeur_s, colonne)+1;
    char* string = malloc((taille+1)*sizeof(char));
    strcpy(string, buffer);
    return string;
}

/* renvoie la contrainte 1 du problème des 5 maisons
 i.e. L'anglais abate dans la maison rouge
 la chaîne de caractère renvoyée doit être free */
char* contrainte1(void){
    int taille = 5;
    char** l = malloc(taille*sizeof(char*));
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(0, 0, i); // rouge
        char* expr2 = variables_maisons(3, 4, i); // anglais
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    free(l);
    
    return result;
}

/* renvoie la contrainte 2 du problème des 5 maisons
 i.e. Le suédois possède un chien comme animal de compagnie
 la chaîne de caractère renvoyée doit être free */
char* contrainte2(void){
    int taille = 5;
    char* l[5];
    
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(4, 1, i); // chien
        char* expr2 = variables_maisons(3, 1, i); // suédois
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 3 du problème des 5 maisons
 i.e. Le danois boit du thé
 la chaîne de caractère renvoyée doit être free */
char* contrainte3(void){
    int taille = 5;
    char* l[5];
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(2, 3, i); // thé
        char* expr2 = variables_maisons(3, 3, i); // danois
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 4 du problème des 5 maisons
 i.e. La maison verte est à gauche de la maison blanche
 la chaîne de caractère renvoyée doit être free */
char* contrainte4(void){
    int taille = 4;
    char* l[4];
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(0, 2, i); // vert
        char* expr2 = variables_maisons(0, 4, i+1); // blanche
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 5 du problème des 5 maisons
 i.e. La personne qui habite dans la maison verte boit du café
 la chaîne de caractère renvoyée doit être free */
char* contrainte5(void){
    int taille = 5;
    char* l[5];
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(0, 2, i); // vert
        char* expr2 = variables_maisons(2, 4, i); // café
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 6 du problème des 5 maisons
 i.e. Le personne qui fait du vélo possède un oiseau
 la chaîne de caractère renvoyée doit être free */
char* contrainte6(void){
    int taille = 5;
    char* l[5];
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(1, 4, i); // vélo
        char* expr2 = variables_maisons(4, 4, i); // oiseau
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 7 du problème des 5 maisons
 i.e. La personne qui habite dans la maison jaune fait de la danse
 la chaîne de caractère renvoyée doit être free */
char* contrainte7(void){
    int taille = 5;
    char*l[5];
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(0, 3, i); // jaune
        char* expr2 = variables_maisons(1, 1, i); // danse
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 8 du problème des 5 maisons
 i.e. La personne dans la maison du centre boit du lait
 la chaîne de caractère renvoyée doit être free */
char* contrainte8(void){
    return variables_maisons(2, 1, 2); // lait
}

/* renvoie la contrainte 9 du problème des 5 maisons
 i.e. Le norvégien habite dans la prière maison
 la chaîne de caractère renvoyée doit être free */
char* contrainte9(void){
    return variables_maisons(3, 2, 0); // norvégien
}

/* renvoie la contrainte 10 du problème des 5 maisons
 i.e. La personne qui fait de l'escalade a un voisin qui a un chat
 la chaîne de caractère renvoyée doit être free */
char* contrainte10(void){
    int taille = 8;
    char* l[8];
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 0, i); // escalade
        char* expr2 = variables_maisons(4, 0, i+1); // chat
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 0, i+1); // escalade
        char* expr2 = variables_maisons(4, 0, i); // chat
        l[taille/2+i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 11 du problème des 5 maisons
 i.e. La personne qui fait de la danse à un voisin qui fait du cheval
 la chaîne de caractère renvoyée doit être free */
char* contrainte11(void){
    int taille = 8;
    char* l[8];
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 1, i); // danse
        char* expr2 = variables_maisons(4, 3, i+1); // cheval
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 1, i+1); // danse
        char* expr2 = variables_maisons(4, 3, i); // cheval
        l[taille/2+i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 12 du problème des 5 maisons
 i.e. La personne qui fait du basket boit du Yop
 la chaîne de caractère renvoyée doit être free */
char* contrainte12(void){
    int taille = 5;
    char* l[5];
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(1, 3, i); // basket
        char* expr2 = variables_maisons(2, 2, i); // yop
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 13 du problème des 5 maisons
 i.e. L'allemand fait du karaté
 la chaîne de caractère renvoyée doit être free */
char* contrainte13(void){
    int taille = 5;
    char* l[5];
    
    for (int i = 0; i< taille; i++){
        char* expr1 = variables_maisons(1, 2, i); // karaté
        char* expr2 = variables_maisons(3, 0, i); // allemand
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, 5);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 14 du problème des 5 maisons
 i.e. Le voisin du norvégien habite dans une maison bleue
 la chaîne de caractère renvoyée doit être free */
char* contrainte14(void){
    int taille = 8;
    char* l[8];
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(0, 1, i); // bleu
        char* expr2 = variables_maisons(3, 2, i+1); // norvégien
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(0, 1, i+1); // bleu
        char* expr2 = variables_maisons(3, 2, i); // norvégien
        l[taille/2+i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte 15 du problème des 5 maisons
 i.e. La personne qui fait de l'escalade à un voisin qui boit de l'eau
 la chaîne de caractère renvoyée doit être free */
char* contrainte15(void){
    int taille = 8;
    char* l[8];
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 0, i); // escalade
        char* expr2 = variables_maisons(2, 0, i+1); // eau
        l[i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    for (int i = 0; i< taille/2; i++){
        char* expr1 = variables_maisons(1, 0, i+1); // escalade
        char* expr2 = variables_maisons(2, 0, i); // eau
        l[taille/2+i] = et(expr1, expr2);
        free(expr1);
        free(expr2);
    }
    
    char* result = ou_liste(l, taille);
    for(int i = 0; i< taille; i++){
        free(l[i]);
    }
    
    return result;
}

/* renvoie la contrainte qu'il ne doit y avoir qu'une seule de chaque valeur sur la ligne n
 la chaîne de caractère renvoyée doit être free */
char* contrainte_ligne(int n){
    char*l[5];
    for (int i = 0; i<5; i++){
        char* variables[5] = {variables_maisons(n, 0, i),variables_maisons(n, 1, i),variables_maisons(n, 2, i),variables_maisons(n, 3, i),variables_maisons(n, 4, i)};
        l[i] = une_seule(variables, 5);
        for (int j = 0; j < 5; j++){
            free(variables[j]);
        }
    }
    char* result = et_liste(l, 5);
    for (int i = 0; i< 5; i++){
        free(l[i]);
    }
    return result;
}

/* renvoie la contrainte qu'il ne doit y avoir qu'un seul élément de chaque catégorie sur le tableau
 la chaîne de caractère renvoyée doit être free */
char* contrainte_placement(int n){
    char*l[5];
    for (int i = 0; i<5; i++){
        char* variables[5] = {variables_maisons(n, i, 0),variables_maisons(n, i, 1),variables_maisons(n, i, 2),variables_maisons(n, i, 3),variables_maisons(n, i, 4)};
        l[i] = une_seule(variables, 5);
        for (int j = 0; j < 5; j++){
            free(variables[j]);
        }
    }
    char* result = et_liste(l, 5);
    for (int i = 0; i< 5; i++){
        free(l[i]);
    }
    return result;
}

int generate_solution_5_maisons(char* filename){
    char* variables[5];
    for (int i = 0; i<5; i++){
        variables[i] = contrainte_ligne(i);
    }
    char* expr1 = et_liste(variables, 5);
    
    for (int i = 0; i<5; i++){
        free(variables[i]);
        variables[i] = contrainte_placement(i);
    }
    char* expr2 = et_liste(variables, 5);
    for (int i = 0; i<5; i++){
        free(variables[i]);
    }
    
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
    
    char* result = et_liste(l, 17);
    
    for (int i = 0; i< 17; i++){
        free(l[i]);
    }
    FILE* file = fopen(filename, "w");
    int len = (int)strlen(result);
    fprintf(file, "%s\n", result);
    fclose(file);
    free(result);
    return len;
}
