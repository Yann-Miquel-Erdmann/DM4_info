#include <stdio.h>
#include "utils.h"
#include "dames/n_dames.h"
#include "taquin/taquin.h"

int main(void){
    FILE* file = fopen("test_taquin_3x3.txt", "w");
    int initial_position[9] = {4, 7, 6, 1, 3, 2, 8, 5, 0};
    char* test = generate_solution(3, initial_position, 9);
    if (!strcmp(test, "")){
        exit(1);
    }
    printf("%s\n", test);
    fprintf(file, "%s", test);
    fclose(file);
    free(test);
}
