# DM4 

## Satsolver OCAML
### compilation
Pour compiler le satsolver OCAML il suffit d'utiliser la commande make
```sh
make OCAML
```

### exécution
Pour résoudre une formule avec le satsolver naif
```sh
./satsolver naif chemin/du/fichier
```


Pour résoudre une formule avec le satsolver optimisé
```sh
./satsolver chemin/du/fichier
```

### tests
Pour lancer une suite de tests du satsolver
```sh
./satsolver test
```
### nettoyer les fichiers temporaires OCAML
```sh
make clean_OCAML
```


## générateur de formules
### compilation
Pour compiler le générateur de formules
```sh
make C
```
### exécution
Pour exécuter le générateur de programmes
```sh
./generateur_de_formules
```
puis suivre les instructions dans le terminal  

### nettoyer les fichiers temporaires C
```sh
make clean_C
```

## tout nettoyer
supprime les fichiers temporaires de C et d'OCAML ainsi que les exécutables
```sh
make clean
```
