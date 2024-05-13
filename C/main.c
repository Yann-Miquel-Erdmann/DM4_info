#include <stdio.h>
#include "utils.h"

int main(void){
    char* l[] = {"A", "B", "(A & ~B)"};
    printf("%s\n", au_moins_une(l, 3));
}
