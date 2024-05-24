/*
régions = {
1:  Auvergne-Rhône-Alpes,
2:  Bourgogne-Franche-Comté,
3:  Bretagne,
4:  Centre-Val-de-Loire,
5:  Corse,
6:  Grand-Est,
7:  Hauts-de-France,
8:  Île-de-France,
9:  Normandie,
10: Nouvelle-Aquitaine,
11: Occitanie,
12: Pays-de-la-Loire,
13: Provence-Alpes-Côte d'Azur
}

Régions voisines = {
1: {2,4,10,11,13},
2: {1,4,6,8},
3: {9,12},
4: {1,2,8,9,10,12},
5: {},
6: {7,8,2},
7: {9,8,6},
8: {7,6,2,4,9},
9: {3,12,4,8,7},
10: {12,4,1,11},
11: {10,1,13},
12: {3,94,10},
13: {1,11}
}



Variable: la région i est de la couleur k = i_k

pour toute région i:
    un seul parmi {i_k pour toute couleur k}
    pour toute couleur k:
        i_k et aucun parmi {j_k pour tout voisin j de i}

*/