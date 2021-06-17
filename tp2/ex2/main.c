/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfichier.h"
#include "pnmio.h"

/** Constantes **/

#define M 20

/** Variables **/

FILE* src = NULL;
FILE* dst = NULL;
int pnm_type;

int* img_data;
long size;

int x_dim, y_dim, level, ascii;

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./quantification <src> <dst>\n"); }

void traitement()
{
    int levels[M];
    int current = 0;
    int sum = img_data[0];
    int interval = size / M;

    long i;
    for (i = 1; i < size; i++) {
        sum += img_data[i];
        if (i % interval == 0) {
            levels[current] = sum / interval;
            // printf("Average level n°%d: %d\n", current, levels[current]);
            current++;
            sum = 0;
        }
    }

    current = 0;
    for (i = 0; i < size; i++) {
        double factor = (double)levels[current] / (double)level;
        img_data[i] = factor * img_data[i];
        if (i != 0 && i % interval == 0) {
            current++;
        }
    }
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 3) {
        usage();
        exit(EXIT_FAILURE);
    }

    /* Open input file */
    src = ouvrir_fichier(argv[1], "r");

    /* Get file type */
    pnm_type = get_pnm_type(src);
    fprintf(stderr, "Info: pnm_type = %d\n", pnm_type);
    rewind(src);

    if (pnm_type == PPM_BINARY || pnm_type == PGM_BINARY) {
        fermer_fichier(src);
        src = ouvrir_fichier(argv[1], "rb");
    }

    /* Read the image file header (the input file has been rewinded). */
    if ((pnm_type == PGM_ASCII) || (pnm_type == PGM_BINARY))
        read_pgm_header(src, &x_dim, &y_dim, &level, &ascii);
    else if ((pnm_type == PPM_ASCII) || (pnm_type == PPM_BINARY))
        read_ppm_header(src, &x_dim, &y_dim, &level, &ascii);
    else {
        fprintf(stderr, "Error: Unknown PNM/PFM image format. Exiting...\n");
        exit(1);
    }

    /* Allocate space for image data storage. */
    if ((pnm_type == PPM_ASCII) || (pnm_type == PPM_BINARY)) {
        size = 3 * x_dim * y_dim;
        img_data = malloc(size * sizeof(int));
    } else {
        size = x_dim * y_dim;
        img_data = malloc(size * sizeof(int));
    }

    /* Read file data */
    if ((pnm_type == PGM_ASCII) || (pnm_type == PGM_BINARY)) {
        read_pgm_data(src, img_data, ascii);
    } else if ((pnm_type == PPM_ASCII) || (pnm_type == PPM_BINARY)) {
        read_ppm_data(src, img_data, ascii);
    }
    printf("size: %lu\n", size);

    /* Edit the image */
    traitement();

    /* Open output file */
    if (ascii) {
        dst = ouvrir_fichier(argv[2], "w");
    } else {
        dst = ouvrir_fichier(argv[2], "wb");
    }

    /* Store image data to PPM file. */
    if ((pnm_type == PGM_ASCII) || (pnm_type == PGM_BINARY))
        write_pgm_file(dst, img_data, x_dim, y_dim, 1, 1, level, 16, ascii);
    else if ((pnm_type == PPM_ASCII) || (pnm_type == PPM_BINARY))
        write_ppm_file(dst, img_data, x_dim, y_dim, 1, 1, level, ascii);

    /* Free image data storage. */
    if (pnm_type == PGM_ASCII || pnm_type == PGM_BINARY || pnm_type == PPM_ASCII || pnm_type == PPM_BINARY)
        free(img_data);

    /* Close source file */
    // fermer_fichier(src);

    /* Close destination file */
    // fermer_fichier(dst);

    return 0;
}