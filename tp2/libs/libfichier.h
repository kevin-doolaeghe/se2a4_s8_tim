#ifndef _LIBFICHIER_H_
#define _LIBFICHIER_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdio.h>

/** Prototypes **/

FILE* ouvrir_fichier(char* fichier, char* mode);
void fermer_fichier(FILE* fp);

#endif