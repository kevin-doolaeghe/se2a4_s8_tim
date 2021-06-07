/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>

#include "libfichier.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./quantification <image>\n"); }

void afficher_contenu(char *contenu) {
    int i;
    for (i = 0; i < LONGUEUR_MAX; i++) {
        printf("%c", contenu[i]);
    }
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    FILE* fichier = ouvrir_fichier(argv[1], "rw");

    char contenu[LONGUEUR_MAX];
    lire_fichier(fichier, contenu);

    afficher_contenu(contenu);

    fermer_fichier(fichier);

    return 0;
}