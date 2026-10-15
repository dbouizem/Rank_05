# polyset

Exercice C++ sur le polymorphisme, l'héritage multiple et la composition.
L'objectif est d'ajouter la recherche à deux collections d'entiers, puis de
les utiliser à travers une classe `set` qui empêche l'ajout de doublons.

## Classes

| Classe | Rôle |
|---|---|
| `bag` | Interface abstraite : insertion, affichage et suppression du contenu. |
| `searchable_bag` | Étend l'interface avec `bool has(int) const`. |
| `array_bag` | Stocke les entiers dans un tableau dynamique. |
| `tree_bag` | Stocke les entiers dans un arbre binaire de recherche. |
| `searchable_array_bag` | Combine `array_bag` et `searchable_bag` ; recherche linéaire dans le tableau. |
| `searchable_tree_bag` | Combine `tree_bag` et `searchable_bag` ; recherche en suivant les branches de l'arbre. |
| `set` | Enveloppe un `searchable_bag` et vérifie la présence d'une valeur avant de l'insérer. |

L'héritage virtuel de `bag` permet de partager une seule base `bag` dans les
classes à héritage multiple. Les appels via un pointeur `searchable_bag *`
utilisent les méthodes de la classe concrète grâce aux fonctions virtuelles.

## Fichiers à rendre

Le sujet demande les six fichiers suivants :

- `searchable_array_bag.hpp` et `searchable_array_bag.cpp` ;
- `searchable_tree_bag.hpp` et `searchable_tree_bag.cpp` ;
- `set.hpp` et `set.cpp`.

Les interfaces et collections de base servent de support. `main.cpp` permet
de tester le résultat, `subject.txt` contient le sujet et `Subject/` conserve
des fichiers de référence.

Les classes demandées suivent la forme canonique : constructeur, constructeur
de copie, opérateur d'affectation et destructeur. Les opérations de lecture
respectent la qualification `const`.

## Utilisation de `set`

```cpp
#include "searchable_array_bag.hpp"
#include "set.hpp"

int main()
{
    searchable_array_bag storage;
    set values(storage);
    int numbers[] = {3, 1, 3, 2};

    values.insert(numbers, 4);
    values.print(); // 3 1 2
    bool found = values.has(3); // true
    (void)found;
    values.clear();
    return 0;
}
```

`set` conserve un pointeur vers la collection passée au constructeur : cette
collection doit donc rester vivante pendant son utilisation. Copier un `set`
partage la même collection ; cela ne copie pas son contenu.

`get_bag()` donne accès à la collection sous-jacente, avec une version constante.
Une insertion directe dans cette collection contourne le contrôle des doublons
de `set`. Les doublons déjà présents avant la création du `set` ne sont pas retirés.

## Compilation et exécution

Depuis `level0/polyset` :

```bash
c++ -std=c++98 -Wall -Wextra -Werror \
    main.cpp array_bag.cpp tree_bag.cpp \
    searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp \
    -o /tmp/polyset

/tmp/polyset 3 1 3 2
```

Le programme de test affiche les collections, vérifie la présence de valeurs,
puis teste leur utilisation avec `set`. Les recherches affichent `1` pour une
valeur présente et `0` pour une valeur absente. Sans argument, il retourne `1`.

Le tableau conserve l'ordre d'insertion. L'arbre affiche les valeurs dans
l'ordre croissant ; dans l'implémentation actuelle, il ignore les doublons
à l'insertion et n'affiche pas la valeur `0`.

