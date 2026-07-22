1. C++ : vect2
2. C++ : bigint
3. C++ : polyset
4. C : life
5. C : bsq

| Exercice    | Langage | De quoi parle l’exercice ?                                                                                      | Notions techniques principales                                                                                              | Difficulté |
| ----------- | ------- | --------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------- | ---------- |
| **vect2**   | C++     | Créer une classe représentant un vecteur avec deux coordonnées `x` et `y`                                       | Classes, constructeurs, forme canonique, `const`, surcharge d’opérateurs, `[]`, `+`, `-`, `*`, `++`, `--`, `==`, `!=`, `<<` | Facile     |
| **bigint**  | C++     | Créer une classe capable de stocker et manipuler des nombres beaucoup plus grands que les types standards       | `std::string`, addition avec retenue, comparaison, surcharge d’opérateurs, incrémentation, décalage décimal                 | Moyen      |
| **polyset** | C++     | Transformer différentes structures de type `bag` en structures recherchables, puis créer un `set` sans doublons | Classes abstraites, héritage multiple, polymorphisme, composition, méthodes virtuelles, forme canonique, `const`            | Difficile  |
| **life**    | C       | Dessiner une grille avec un stylo commandé par `w`, `a`, `s`, `d`, `x`, puis simuler le jeu de la vie           | `read`, tableaux 2D, allocation dynamique, coordonnées, comptage des voisins, double grille, simulation                     | Moyen      |
| **bsq**     | C       | Lire une carte et trouver le plus grand carré ne contenant aucun obstacle                                       | Fichiers, `getline`, `fopen`, allocation dynamique, validation de données, programmation dynamique, gestion des erreurs     | Difficile  |

### Ordre de progression

| Langage | Ordre recommandé               |
| ------- | ------------------------------ |
| **C++** | `vect2` → `bigint` → `polyset` |
| **C**   | `life` → `bsq`                 |
