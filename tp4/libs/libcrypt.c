/** Fichiers d'inclusion **/

#include "libcrypt.h"

/** Fonctions **/

char isKeyValid(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 1;
    else
        return 0;
}

char* generateKey(char* str, char* keyword)
{
    int size = strlen(str);
    char* key = malloc(size);

    int i, j;
    for (i = 0, j = 0; i < size; i++, j++) {
        if (j == strlen(keyword))
            j = 0;
        key[i] = keyword[j];
    }
    return key;
}

char* cipherText(char* str, char* key)
{
    int size = strlen(str);
    char* cipher_text = malloc(size);

    int i;
    for (i = 0; i < size; i++) {
        if (isKeyValid(str[i]))
            cipher_text[i] = (str[i] + key[i]) % 26 + 'A';
        else
            cipher_text[i] = str[i];
    }
    return cipher_text;
}

char* originalText(char* cipher_text, char* key)
{
    int size = strlen(cipher_text);
    char* orig_text = malloc(size);

    int i;
    for (i = 0; i < size; i++) {
        if (isKeyValid(cipher_text[i]))
            orig_text[i] = (cipher_text[i] - key[i] + 26) % 26 + 'A';
        else
            orig_text[i] = cipher_text[i];
    }
    return orig_text;
}
