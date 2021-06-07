/** Fichiers d'inclusion **/

#include "libfichier.h"

/** Fonctions **/

FILE* ouvrir_fichier(char* fichier, char* mode) {
    FILE* fp;
    fp = fopen(fichier, mode);

    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier.\n");
        return NULL;
    }

    return fp;
}

void lire_fichier(FILE* fp, char *contenu) {
    char ligne[LONGUEUR_MAX];
    int  nb_lignes = 0;

    while (fscanf(fp, "%[^\n]\n", ligne) != EOF) {
        // printf("%s\n", ligne);
        strcat(contenu, ligne);
        nb_lignes++;
    }

    if (feof(fp)) { printf("Le fichier a été lu avec succès : %d lignes lues.\n", nb_lignes); }
    if (ferror(fp)) { printf("Une erreur est survenue lors de la lecture du fichier !\n"); }
}

void fermer_fichier(FILE* fp) { fclose(fp); }