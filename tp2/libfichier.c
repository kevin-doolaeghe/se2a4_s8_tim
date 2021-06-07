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

str_list_t* lire_fichier(FILE* fp)
{
    str_list_t* contenu = malloc(sizeof(str_list_t));
    init_str_list(contenu);

    char ligne[LONGUEUR_MAX];
    int nb_lignes = 0;

    while (fscanf(fp, "%[^\n]\n", ligne) != EOF) {
        append_cstr_to_list(contenu, ligne);
        nb_lignes++;
    }

    if (feof(fp))
        printf("Le fichier a été lu avec succès : %d lignes lues.\n", nb_lignes);
    if (ferror(fp))
        printf("Une erreur est survenue lors de la lecture du fichier !\n");

    return contenu;
}

void fermer_fichier(FILE* fp) { fclose(fp); }