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

void usage() { fprintf(stderr, "Syntaxe : ./chiffrement <keyword> <message>\n"); }

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

    char* message = malloc(MAX_LEN);
    strcpy(message, "");
    for (i = 0; i < argc - 2; i++) {
        strcat(message, argv[2 + i]);
        if (i != argc - 3)
            strcat(message, " ");
    }
    printf("Given message: %s\n\n", message);

    int delta = 0;
    for (i = 0; i < strlen(keyword); i++) {
        if (isKeyValid(keyword[i]))
            keyword[i - delta] = toupper(keyword[i]);
        else
            delta++;
    }
    keyword[i - delta] = 0;
    printf("To uppercase keyword: %s\n", keyword);

    for (i = 0; i < strlen(message); i++) {
        if (isKeyValid(message[i]))
            message[i] = toupper(message[i]);
    }
    printf("To uppercase message: %s\n\n", message);

    char* key = generateKey(message, keyword);
    printf("Key: %s\n", key);

    char* cipher = cipherText(message, key);
    printf("Encrypted message: %s\n", cipher);

    free(keyword);
    free(message);
    free(key);
    free(cipher);

    return 0;
}
