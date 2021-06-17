#ifndef _LIBCRYPT_H_
#define _LIBCRYPT_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Prototypes **/

char isKeyValid(char c);
char* generateKey(char* str, char* keyword);
char* cipherText(char* str, char* key);
char* originalText(char* cipher_text, char* key);

#endif