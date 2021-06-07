# SE2A4 | Semestre n°8 - TIM - TP Postscript

## Auteur

### Kevin Doolaeghe

## Objectif

Mise en pratique du langage Postscript d'Adobe.

## Installation de Ghostscript :

```
sudo apt install ghostscript
```

L'utilitaire Okular peut également être installé pour visualiser rapidement le rendu du script :

```
sudo apt install okular
```

L'utilitaire GhostView (`gv`) permet aussi d'effectuer la même opération.

## Sources

* Documentation Postscript d'Adobe :
https://www.adobe.com/jp/print/postscript/pdfs/PLRM.pdf

* Résumé des commandes principales :
https://melusine.eu.org/syracuse/texpng/ps_commands/ps_commands/?page=1

* Tutoriel Postscript :
http://paulbourke.net/dataformats/postscript/

## Utilisation

Pour lancer un script Postscript (extension `.ps`),  il faut utiliser la commande `gs` :

```
gs [options] [files]
```

Par exemple, pour générer un fichier `pdf` à partir du fichier `script.ps`, il faut entrer la commande :

```
gs -sOutputFile=resultat.pdf script.ps
```

## Fonctionnement de Postscript

### Langage à pile :

Il s'agit d'un langage à pile et postfixé.  
Ainsi, `4 3 2 add mul` effectue le calcul `(4+3)x2=14`.

### Gestion du contexte :

Postscript est également un langage à contexte.  
En effet, les composants utilisent des paramètres par défaut.  
La modification d'un paramètre prend effet sur les instructions suivantes.

Il est possible de sauvegarder l'état du contexte avant d'effectuer des modifications avec la primitive `gsave`.  
Pour restaurer le contexte sauvegardé, il faut utiliser la primitive `grestore`.

### Centre graphique :

Le (0, 0) est situé en bas à gauche de la page.

### Procédures :

Une procédure peut être définie de la façon suivante :

```
/box {
    newpath
    0 0 moveto
    0 1 lineto
    1 1 lineto
    1 0 lineto
    closepath
} def
```

### Variables

Une variable peut être définie de la façon suivante :

```
/PI 3.14 def
```

Il est possible de récupérer la valeur au sommet de la pile pour la stocker dans une variable :

```
/x exch def
/y exch def
```

### Transformations :

Les transformations suivantes peuvent être effectuées sur les objets :
* `translate` : translation
* `rotate` : rotation
* `scale` : homothétie

### Primitives pour le dessin graphique :

* `fill` : remplir une zone graphique délimitée par le tracé
* `stroke` : dessiner les lignes du tracé sur la page 
* `image` : afficher une image
* `show` : dessiner des caractères
* `newpath` : initialiser un nouveau tracé
* `closepath` : fermer la figure tracée (cela relie le premier et le dernier point)
* `lineto` permet de tracer un segment entre deux points par rapport au centre tandis que `rlineto` trace le segment de manière relative par rapport à la position actuelle
* `arc` permet de tracer un arc