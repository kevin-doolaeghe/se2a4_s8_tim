/** Fichiers d'inclusion **/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libcrypt.h"

/** Constantes **/

#define MAX_LEN 1000

/** Variables **/

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./dechiffrement <key> <cipher>\n"); }

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc < 3) {
        usage();
        exit(EXIT_FAILURE);
    }

    int i;

    char* keyword = malloc(strlen(argv[1]));
    strcpy(keyword, argv[1]);
    printf("Given keyword: %s\n", keyword);

    char* cipher = malloc(MAX_LEN);
    strcpy(cipher, "");
    for (i = 0; i < argc - 2; i++) {
        strcat(cipher, argv[2 + i]);
        if (i != argc - 3)
            strcat(cipher, " ");
    }
    printf("Given cipher: %s\n\n", cipher);

    int delta = 0;
    for (i = 0; i < strlen(keyword); i++) {
        if (isKeyValid(keyword[i]))
            keyword[i - delta] = toupper(keyword[i]);
        else
            delta++;
    }
    keyword[i - delta] = 0;
    printf("To uppercase keyword: %s\n\n", keyword);

    char* key = generateKey(cipher, keyword);
    printf("Key: %s\n\n", key);

    char* original = originalText(cipher, key);
    printf("Original message: %s\n", original);

    free(keyword);
    free(key);
    free(cipher);
    free(original);

    return 0;
}