/**** Bibliotheque de threading ****/

#ifndef _LIBFICHIER_H_
#define _LIBFICHIER_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdio.h>

#include "libstrlist.h"

/** Constantes **/

#define LONGUEUR_MAX 100000
#define NB_LIGNES 1000

/** Prototypes **/

FILE* ouvrir_fichier(char* fichier, char* mode);
str_list_t* lire_fichier(FILE* fp);
void fermer_fichier(FILE* fp);

#endif