/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>

#include "libfichier.h"
#include "libimage.h"
#include "libppm.h"
#include "libstrlist.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./quantification <image>\n"); }

void afficher_fichier(str_list_t* contenu)
{
    int i, j;
    for (i = 0; i < contenu->alloc; i++) {
        printf("Part %d | len: %d\nstr: ", i, contenu->str_list[i].alloc);
        for (j = 0; j < contenu->str_list[i].alloc - 1; j++)
            printf("%c ", contenu->str_list[i].data[j] & 0xff);
        printf("\n\n");
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

    /*
    FILE* fichier = ouvrir_fichier(argv[1], "rw");
    str_list_t* contenu = lire_fichier(fichier);

    afficher_fichier(contenu);

    fermer_fichier(fichier);
    destroy_str_list(contenu);
    */

    /*
    PPMImage* image;
    image = readPPM(argv[1]);
    changeColorPPM(image);
    writePPM(argv[1], image);
    printf("Press any key...");
    getchar();
    */

    unsigned char* data;
    int width, height;

    if ((argc > 1) && ((data = load_pixmap(argv[1], &width, &height)) != NULL))
        store_pixmap("clone.pgm", data, width, height);

    /*
    unsigned char *data_R, *data_G, *data_B;
    int width, height;

    if( (argc > 1) && load_RGB_pixmap(argv[1], &width, &height, &data_R, &data_G, &data_B) )
        store_RGB_pixmap("GBR.pnm", data_G, data_B, data_R, width, height);
    */

    return 0;
}