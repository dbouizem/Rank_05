# life

Le **jeu de la vie**, c’est une grille avec des cellules qui peuvent être
**vivantes ou mortes**. On choisit le dessin de départ, puis on regarde comment
il évolue tout seul.

Pour comprendre les dessins : **🟩 = cellule vivante** et **⬜ = cellule morte**.

## Le dessin de départ

Imagine cette grille avec trois cellules vivantes au milieu :

⬜⬜⬜⬜⬜<br>
⬜⬜🟩⬜⬜<br>
⬜⬜🟩⬜⬜<br>
⬜⬜🟩⬜⬜<br>
⬜⬜⬜⬜⬜

## Les huit voisines

**Chaque cellule regarde les huit cases autour d’elle**, y compris en diagonale.
Voici les voisines de la cellule marquée 🔴 :

⬜⬜⬜⬜⬜<br>
⬜🟨🟨🟨⬜<br>
⬜🟨🔴🟨⬜<br>
⬜🟨🟨🟨⬜<br>
⬜⬜⬜⬜⬜

Les huit cases jaunes sont ses voisines. **La cellule centrale ne se compte pas
elle-même.** Dans cet exercice, les cellules à l’extérieur de la grille sont
considérées comme mortes : les bords ne se rejoignent pas.

## Les règles à chaque tour

- Une cellule vivante **survit si elle a 2 ou 3 voisines vivantes**.
- Une cellule vivante **meurt si elle en a moins de 2 ou plus de 3**.
- Une cellule morte **devient vivante si elle a exactement 3 voisines vivantes**.
- Dans tous les autres cas, une cellule morte reste morte.

## Exemple : une ligne qui change de sens

Regardons ce qui arrive à notre ligne verticale.

1. **La cellule du haut meurt.** Elle n’a qu’une seule voisine vivante : celle du milieu.
2. **La cellule du milieu survit.** Elle a deux voisines vivantes : celle du haut et celle du bas.
3. **La cellule du bas meurt.** Elle n’a qu’une seule voisine vivante : celle du milieu.
4. **Une cellule naît à gauche et une autre à droite du milieu.** Chacune touche les trois cellules de la ligne de départ, en comptant les diagonales !

On obtient donc, **au tour suivant** :

⬜⬜⬜⬜⬜<br>
⬜⬜⬜⬜⬜<br>
⬜🟩🟩🟩⬜<br>
⬜⬜⬜⬜⬜<br>
⬜⬜⬜⬜⬜

**La ligne verticale est devenue horizontale.** Au tour d’après, elle redevient verticale :

⬜⬜⬜⬜⬜<br>
⬜⬜🟩⬜⬜<br>
⬜⬜🟩⬜⬜<br>
⬜⬜🟩⬜⬜<br>
⬜⬜⬜⬜⬜

Ce motif s’appelle un **clignotant** : il alterne entre ces deux formes.

## Tout change en même temps

**Pour calculer un tour, on regarde toujours le dessin du tour précédent.**
On ne compte jamais une cellule qui vient de naître pendant le calcul, et une
cellule qui va mourir compte encore parmi les voisines vivantes de ce tour.

En pratique, on peut utiliser deux grilles :

- **La grille actuelle**, que l’on lit pour compter les voisines.
- **La grille suivante**, dans laquelle on écrit le résultat des règles.

Une fois toutes les cellules calculées, la grille suivante devient la grille actuelle.

## Le lien avec l’exercice

Le programme s’utilise ainsi :

```sh
./life largeur hauteur iterations
```

Tu dessines d’abord les cellules de départ avec un stylo qui commence en haut à
gauche de la grille. Les commandes sont lues sur l’entrée standard :

| Commande | Action |
| --- | --- |
| `w` | Déplacer le stylo vers le haut |
| `a` | Déplacer le stylo vers la gauche |
| `s` | Déplacer le stylo vers le bas |
| `d` | Déplacer le stylo vers la droite |
| `x` | Baisser ou lever le stylo pour commencer ou arrêter de dessiner |

À la fin de l’entrée, le programme fait évoluer ce dessin pendant le nombre de
tours demandé, puis affiche la grille finale : **`O` pour une cellule vivante**
et **un espace pour une cellule morte**.

Avec **0 itération**, il affiche simplement le dessin de départ.

## Compiler et essayer

Depuis le dossier `level1/life` :

```sh
cc -Wall -Wextra -Werror -std=c99 life.c -o life
```

Pour dessiner une ligne verticale sans la faire évoluer :

```sh
echo 'dxss' | ./life 3 3 0 | cat -e
```

Résultat (`$` indique la fin de chaque ligne, grâce à `cat -e`) :

```text
 O $
 O $
 O $
```

Avec un tour, elle devient horizontale :

```sh
echo 'dxss' | ./life 3 3 1 | cat -e
```

```text
   $
OOO$
   $
```

Le stylo commence **levé**. Le premier `x` le baisse et rend sa case vivante.
Tant qu’il est baissé, chaque déplacement rend la case atteinte vivante. Le
lever n’efface aucune cellule.

Le sujet ne précise pas les déplacements du stylo hors de la grille : cette
solution les ignore et garde le stylo sur le bord. Les caractères autres que
`w`, `a`, `s`, `d` et `x`, comme le retour à la ligne de `echo`, sont ignorés.

## Lire le code

La solution est dans [`life.c`](life.c). La grille est stockée dans un seul
tableau : la case de colonne `x` et de ligne `y` se trouve à l’indice
`y * largeur + x`. Les coordonnées commencent à `0`.

| Fonction | Rôle |
| --- | --- |
| `parse_number` | Lire un entier positif ou nul sans dépasser la capacité d’un `int` |
| `draw_board` | Lire les commandes et construire le dessin de départ |
| `count_neighbors` | Compter les voisines vivantes à l’intérieur de la grille |
| `next_generation` | Calculer toutes les cellules du prochain tour |
| `print_board` | Afficher la grille finale avec `O`, des espaces et des retours à la ligne |
| `main` | Vérifier les arguments, allouer les deux grilles, lancer les tours et libérer la mémoire |

La largeur et la hauteur doivent être strictement positives ; le nombre de
tours peut être nul. Les arguments invalides, les échecs d’allocation et les
erreurs de lecture font quitter le programme avec le code `1`.

## Lancer les tests

```sh
python3 tests/test_life.py
```

Les tests compilent le programme dans un dossier temporaire. Ils vérifient les
exemples du sujet, le stylo, les bords, les arguments invalides et 80 motifs
aléatoires comparés à une simulation de référence.

