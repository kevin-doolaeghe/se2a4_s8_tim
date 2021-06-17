/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfichier.h"
#include "pnmio.h"

/** Constantes **/

#define N 1

/** Variables **/

FILE* src = NULL;
FILE* dst = NULL;
int pnm_type;

int* img_data;
long size;

int x_dim, y_dim, level, ascii;

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./quantification <src> <dst>\n"); }

/* Pseudo-code (Wikipedia) :

    for each y from top to bottom do
        for each x from left to right do
            oldpixel := pixel[x][y]
            newpixel := find_closest_palette_color(oldpixel)
            pixel[x][y] := newpixel
            quant_error := oldpixel - newpixel
            pixel[x + 1][y    ] := pixel[x + 1][y    ] + quant_error × 7 / 16
            pixel[x - 1][y + 1] := pixel[x - 1][y + 1] + quant_error × 3 / 16
            pixel[x    ][y + 1] := pixel[x    ][y + 1] + quant_error × 5 / 16
            pixel[x + 1][y + 1] := pixel[x + 1][y + 1] + quant_error × 1 / 16

    find_closest_palette_color(oldpixel) = round(oldpixel / 256)

*/

void traitement()
{
    int y, x;
    int delta, old, new, err;
    if (pnm_type == PGM_ASCII || pnm_type == PGM_BINARY) {
        for (y = 0; y < y_dim; y++) {
            for (x = 0; x < x_dim; x++) {
                if (y % 2 == 0) {
                    delta = y * x_dim + x;
                    old = img_data[delta];
                    new = (N * old / level) * (level / N);
                    img_data[delta] = new;
                    err = old - new;

                    if (delta + 1 < size)
                        img_data[delta + 1] += err * 7.0 / 16.0;
                    if (delta + x_dim - 1 < size)
                        img_data[delta + x_dim - 1] += err * 3.0 / 16.0;
                    if (delta + x_dim < size)
                        img_data[delta + x_dim] += err * 5.0 / 16.0;
                    if (delta + x_dim + 1 < size)
                        img_data[delta + x_dim + 1] += err * 1.0 / 16.0;
                } else {
                    delta = (y + 1) * x_dim - x - 1;
                    old = img_data[delta];
                    new = (N * old / level) * (level / N);
                    img_data[delta] = new;
                    err = old - new;

                    if (delta - 1 < size)
                        img_data[delta - 1] += err * 7.0 / 16.0;
                    if (delta + x_dim + 1 < size)
                        img_data[delta + x_dim + 1] += err * 3.0 / 16.0;
                    if (delta + x_dim < size)
                        img_data[delta + x_dim] += err * 5.0 / 16.0;
                    if (delta + x_dim - 1 < size)
                        img_data[delta + x_dim - 1] += err * 1.0 / 16.0;
                }
            }
        }
    } else if (pnm_type == PPM_ASCII || pnm_type == PPM_BINARY) {
        for (y = 0; y < y_dim; y++) {
            for (x = 0; x < x_dim; x++) {
                int i;
                for (i = 0; i < 3; i++) {
                    if (y % 2 == 0) {
                        delta = y * 3 * x_dim + 3 * x + i;
                        old = img_data[delta];
                        new = (N * old / level) * (level / N);
                        img_data[delta] = new;
                        err = old - new;

                        if (delta + 3 < size)
                            img_data[delta + 3] += err * 7.0 / 16.0;
                        if (delta + 3 * x_dim - 3 < size)
                            img_data[delta + 3 * x_dim - 3] += err * 3.0 / 16.0;
                        if (delta + 3 * x_dim < size)
                            img_data[delta + 3 * x_dim] += err * 5.0 / 16.0;
                        if (delta + 3 * x_dim + 3 < size)
                            img_data[delta + 3 * x_dim + 3] += err * 1.0 / 16.0;
                    } else {
                        delta = (y + 1) * 3 * x_dim - 4 * x + i;
                        old = img_data[delta];
                        new = (N * old / level) * (level / N);
                        img_data[delta] = new;
                        err = old - new;

                        if (delta - 3 < size)
                            img_data[delta - 3] += err * 7.0 / 16.0;
                        if (delta + 3 * x_dim + 3 < size)
                            img_data[delta + 3 * x_dim + 3] += err * 3.0 / 16.0;
                        if (delta + 3 * x_dim < size)
                            img_data[delta + 3 * x_dim] += err * 5.0 / 16.0;
                        if (delta + 3 * x_dim - 3 < size)
                            img_data[delta + 3 * x_dim - 3] += err * 1.0 / 16.0;
                    }
                }
            }
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