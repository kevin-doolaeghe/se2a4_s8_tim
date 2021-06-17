/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfichier.h"
#include "pnmio.h"

/** Constantes **/

#define LINE_FEED '\0'
#define MAX_LEN 1000

/** Variables **/

FILE* src = NULL;
FILE* dst = NULL;
int pnm_type;

int* img_data;
long size;

int x_dim, y_dim, level, ascii;

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./stenographie <src> <dst> <msg>\n"); }

void traitement(char* message)
{
    int x, y;
    int min_size = (strlen(message) + 1) * 4; // 2 bits par pixel
    printf("pixels size: %lu, min_size: %d\n", size / 3, min_size);
    if (min_size > size / 3)
        return;

    int cur = 0;
    int shift = 0;
    for (y = 0; y < y_dim; y++) {
        for (x = 0; x < x_dim; x++) {
            int delta = y * 3 * x_dim + 3 * x + 2; // Composante bleue
            img_data[delta] = img_data[delta] * 3.0 / 4.0; // Quantification 8 bits vers 6 bits
            img_data[delta] = (img_data[delta] << 2) & 0xFF; // Décalage de 2 bits

            if (cur == strlen(message)) {
                img_data[delta] |= (LINE_FEED >> (6 - shift)) & 0x03; // Ajout du caractère de fin
            } else {
                img_data[delta] |= (message[cur] >> (6 - shift)) & 0x03; // Ajout du message
            }

            shift += 2;
            if (shift % 8 == 0) {
                shift = 0;
                cur++;
            }

            if (cur == strlen(message) + 1)
                return;
        }
    }
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc < 4) {
        usage();
        exit(EXIT_FAILURE);
    }

    /* Open input file */
    src = ouvrir_fichier(argv[1], "r");

    /* Get file type */
    pnm_type = get_pnm_type(src);
    fprintf(stderr, "Info: pnm_type = %d\n", pnm_type);
    rewind(src);

    /* Read the image file header (the input file has been rewinded). */
    if ((pnm_type == PPM_ASCII))
        read_ppm_header(src, &x_dim, &y_dim, &level, &ascii);
    else {
        fprintf(stderr, "Error: Unknown PNM/PFM image format. Exiting...\n");
        exit(1);
    }

    /* Allocate space for image data storage. */
    size = 3 * x_dim * y_dim;
    img_data = malloc(size * sizeof(int));

    /* Read file data */
    read_ppm_data(src, img_data, ascii);
    printf("size: %lu\n", size);

    /* Close source file */
    fermer_fichier(src);

    /* Edit the image */
    char* message = malloc(MAX_LEN);
    strcpy(message, "");
    int i;
    for (i = 0; i < argc - 3; i++) {
        strcat(message, argv[3 + i]);
        if (i != argc - 4)
            strcat(message, " ");
    }
    printf("adding following sentence to image: %s\n", message);
    traitement(message);
    free(message);

    /* Open output file */
    dst = ouvrir_fichier(argv[2], "w");

    /* Store image data to PPM file. */
    write_ppm_file(dst, img_data, x_dim, y_dim, 1, 1, level, ascii);

    /* Free image data storage. */
    free(img_data);

    /* Close destination file */
    // fermer_fichier(dst);

    return 0;
}