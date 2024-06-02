#include <stdio.h>
#include "utils.h"
#include "dames/n_dames.h"
#include "taquin/taquin.h"
#include "5_maisons/5_maisons.h"

int main(void){
    /*FILE* file = fopen("test_5_maisons.txt", "w");
    char* test = generate_solution_5_maisons();
    printf("%s\n", test);
    fprintf(file, "%s", test);
    fclose(file);
    free(test);
    
    return 0;*/
    /*gen_formule_n_dames(5, "5dames.txt");*/
    
    FILE* file = fopen("test_taquin_3x3.txt", "w");
    int initial_position[9] = {1, 2, 3, 4, 6, 9, 7, 5, 8};
    char* test = generate_solution(3, initial_position, 9);
    if (!strcmp(test, "")){
        exit(1);
    }
    printf("%s\n", test);
    fprintf(file, "%s", test);
    fclose(file);
    free(test);
    
    /*char* test = generate_move(3, 0);
    printf("%s\n", test);
    free(test);*/
}
