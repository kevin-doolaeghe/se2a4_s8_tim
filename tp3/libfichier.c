/** Fichiers d'inclusion **/

#include "libfichier.h"

/** Fonctions **/

FILE* ouvrir_fichier(char* fichier, char* mode)
{
    FILE* fp;
    fp = fopen(fichier, mode);

    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier.\n");
        return NULL;
    }

    return fp;
}

void fermer_fichier(FILE* fp) { fclose(fp); }