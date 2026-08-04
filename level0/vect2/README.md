# vect2

## Description

`vect2` est une classe C++ représentant un vecteur mathématique de dimension 2.
Ses deux composantes, `x` et `y`, sont des nombres entiers.

Cet exercice permet de pratiquer :

- la forme canonique d'une classe C++ ;
- la surcharge d'opérateurs ;
- les références et les références constantes ;
- la séparation entre le fichier d'en-tête et le fichier d'implémentation.

## Fichiers

- `vect2.hpp` : déclaration de la classe et des opérateurs ;
- `vect2.cpp` : implémentation des constructeurs et des opérateurs ;
- `main.cpp` : fichier utilisé localement pour tester la classe.

Les fichiers demandés pour le rendu sont uniquement `vect2.hpp` et `vect2.cpp`.

## Fonctionnalités

La classe prend en charge :

- la construction par défaut avec la valeur `{0, 0}` ;
- la construction avec deux entiers ;
- la copie et l'affectation ;
- l'accès aux composantes avec `operator[]` ;
- l'addition et la soustraction de deux vecteurs ;
- la multiplication d'un vecteur par un entier ;
- les opérateurs composés `+=`, `-=` et `*=` ;
- les pré-incrémentations et post-incrémentations ;
- les pré-décrémentations et post-décrémentations ;
- l'opposé d'un vecteur avec l'opérateur unaire `-` ;
- les comparaisons `==` et `!=` ;
- l'affichage avec `operator<<`.

## Exemple

```cpp
#include "vect2.hpp"
#include <iostream>

int main()
{
    vect2 first(1, 2);
    vect2 second(3, 4);
    vect2 result = first + second;

    std::cout << result << std::endl;
    std::cout << result * 2 << std::endl;
    return 0;
}
```

Résultat :

```text
{4, 6}
{8, 12}
```

## Compilation

Depuis le dossier `level0/vect2` :

```bash
c++ -std=c++98 -Wall -Wextra -Werror main.cpp vect2.cpp -o vect2
```

## Exécution

```bash
./vect2
```

## Format d'affichage

Un vecteur est affiché sous la forme suivante :

```text
{x, y}
```

Par exemple, `vect2(1, 2)` est affiché ainsi :

```text
{1, 2}
```

| Expression du `main` | Opérateur nécessaire |
|---|---|
| `v1[0]` | `operator[]` |
| `v1[1] = 12` | `operator[]` modifiable |
| `v3[1]` avec `v3` constant | `operator[] const` |
| `std::cout << v1` | `operator<<` |
| `v4++` | `operator++(int)` postfixe |
| `++v4` | `operator++()` préfixe |
| `v4--` | `operator--(int)` postfixe |
| `--v4` | `operator--()` préfixe |
| `v2 += v3` | `operator+=` |
| `v1 -= v2` | `operator-=` |
| `v3 + v3` | `operator+` |
| `v1 - v1` | `operator-` binaire |
| `v3 * 2` | `operator*(int)` |
| `3 * v2` | opérateur libre `operator*(int, vect2)` |
| `v1 *= 42` | `operator*=` |
| `-v2` | `operator-()` unaire |
| `v1 == v3` | `operator==` |
| `v1 != v3` | `operator!=` |
