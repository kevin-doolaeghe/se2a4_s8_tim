# SE2A4 | Semestre n°8 - TIM - TP Quantification

## Auteur

### Kevin Doolaeghe

## Objectif

Réaliser un programme en C qui effectue la compression par quantification d'une image.

## Compilation et lancement

Un exemple de lancement du programme est fourni dans le script `run.sh` et peut être démarré avec la commande :

```
./run.sh
```

- - - - -

## Description du travail réalisé

Les exercices réalisés permettent la compression d'une image :
* par quantification uniforme
* par quantification adaptative
* par l'algorithme de Floyd-Steinberg

En lançant l'exemple fourni, on remarque que la compression par quantification uniforme est la moins performante.
D'un autre côté, l'algorithme de Floyd-Steinberg donne le meilleur résultat.

- - - - -

## Portable pixmap

> Le **portable pixmap file format** (**PPM**), le **portable graymap file format** (**PGM**) et le portable bitmap file format (PBM) sont des formats de fichier graphique utilisés pour les échanges. Ils ont été définis et sont utilisés par le projet NetPBM. Ils proposent des fonctionnalités élémentaires et sont utilisés pour convertir les fichiers de type pixmap, graymap et bitmap entre différentes plateformes. Plusieurs applications désignent cet ensemble de trois formats comme le format **PNM** (**portable anymap**).

Wikipedia | https://fr.wikipedia.org/wiki/Portable_pixmap

## Structure & format

>Les fichiers **PBM**, **PGM** ou **PPM** sont composés sur la même base :
>* le nombre magique du format (deux octets) : il indique le type de format (PBM, PGM, ou PPM) et la variante (binaire ou ASCII)
>* un caractère d'espacement (espace, tabulation, nouvelle ligne)
>* la largeur de l'image (nombre de pixels, écrit explicitement sous forme d'un nombre en caractères ASCII)
>* un caractère d'espacement
>* la hauteur de l'image (idem)
>* un caractère d'espacement
>* les données de l'image : succession des valeurs associées à chaque pixel
>  * l'image est codée ligne par ligne en partant du haut
>  * chaque ligne est codée de gauche à droite.
>
>Toutes les lignes commençant par un croisillon `#` sont ignorées (lignes de commentaires).

Wikipedia | https://fr.wikipedia.org/wiki/Portable_pixmap

### 1. PGM

Une image au format PGM est constituée de nuances de gris.

* Un fichier pgm binaire a pour nombre magique P5.
* Un fichier pgm ASCII a pour nombre magique P2.

```
P2
# Affiche le mot "GG"
12 7
15
0  0  0  0  0  0  0  0  0  0  0  0
0  3  3  3  3  0  0  7  7  7  7  0
0  3  0  0  0  0  0  7  0  0  0  0
0  3  0  3  3  0  0  7  0  7  7  0
0  3  0  0  3  0  0  7  0  0  7  0
0  3  3  3  3  0  0  7  7  7  7  0
0  0  0  0  0  0  0  0  0  0  0  0
```

### 2. PPM

Ce format est utilisé pour des images en couleur.

* Un fichier ppm binaire a pour nombre magique P6.
* Un fichier ppm ASCII a pour nombre magique P3.

```
P3
# P3 = RGB ASCII
3 2
# 3 colonnes x 2 lignes
255
# 255 pour valeur maximum
255  0   0     0  255  0       0   0  255
255 255  0    255 255 255      0   0   0
```

- - - - -

## Bibliothèque utilisée

Afin de réaliser le traitement d'images au format PPM ou PGM, ce TP utilise la bibliothèque suivante :

https://github.com/nkkav/libpnmio