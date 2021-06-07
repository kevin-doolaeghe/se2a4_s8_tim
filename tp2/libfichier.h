/**** Bibliotheque de threading ****/

#ifndef _LIBFICHIER_H_
#define _LIBFICHIER_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdio.h>
#include <string.h>

/** Constantes **/

#define LONGUEUR_MAX 100000

/** Prototypes **/

FILE* ouvrir_fichier(char* fichier, char* mode);
void lire_fichier(FILE* fp, char *contenu);
void fermer_fichier(FILE* fp);

#endif