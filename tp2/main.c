/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>

#include "libfichier.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./quantification <image>\n"); }

void afficher_fichier(str_list_t* contenu)
{
    int i, j;
    for (i = 0; i < contenu->alloc; i++) {
        printf("len: %d\nstr: ", contenu->str_list[i].alloc);
        for (j = 0; j < contenu->str_list[i].alloc; j++)
            printf("%#2x ", contenu->str_list[i].data[j] & 0xff);
        printf("\n\n");
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
    str_list_t* contenu = lire_fichier(fichier);

    afficher_fichier(contenu);

    fermer_fichier(fichier);
    destroy_str_list(contenu);

    return 0;
}