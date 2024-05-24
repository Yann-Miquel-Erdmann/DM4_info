#include "utils.h"

/*
Variable: il y a l'entier k dans la case i j = i_j_k
Un seul par ligne
    pour toute ligne i
        pour tout entier k :
            un seul parmi {i_j_k (pout toute colone j)}

Un seul par colone
    pour toute colone j
        pour tout entier k :
            un seul parmi {i_j_k (pout toute ligne i)}

Un seul par carré
    pour tout carré c de coordonnées (i0, j0)
        pour tout entier k :
            un seul parmi {i_j_k (pout tout (i,j) E [i0, i0+2]x[j0, j0+2])}

*/