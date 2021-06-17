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

void usage() { fprintf(stderr, "Syntaxe : ./stenographie <src>\n"); }

void traitement()
{
    int x, y;
    char* message = malloc(MAX_LEN);
    for (x = 0; x < MAX_LEN; x++)
        message[x] = 0;

    int cur = 0;
    int shift = 0;
    for (y = 0; y < y_dim; y++) {
        for (x = 0; x < x_dim; x++) {
            int delta = y * 3 * x_dim + 3 * x + 2; // Composante bleue
            message[cur] |= (img_data[delta] & 0x03) << (6 - shift); // Récupération du message
            shift += 2;
            if (shift % 8 == 0) {
                shift = 0;
                if (message[cur] == LINE_FEED) {
                    printf("message: %s\n", message);
                    free(message);
                    return;
                }
                cur++;
            }
        }
    }
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 2) {
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
    traitement(argv[3]);

    /* Free image data storage. */
    free(img_data);

    return 0;
}