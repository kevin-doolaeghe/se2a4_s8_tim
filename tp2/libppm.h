#ifndef _LIBPPM_H_
#define _LIBPPM_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdio.h>
#include <stdlib.h>

/** Constantes **/

#define CREATOR "Kevin DOOLAEGHE"
#define RGB_COMPONENT_COLOR 255

/** Variables **/

typedef struct {
    unsigned char red, green, blue;
} PPMPixel;

typedef struct {
    int x, y;
    PPMPixel* data;
} PPMImage;

/** Prototypes **/

PPMImage* readPPM(const char* filename);
void writePPM(const char* filename, PPMImage* img);
void changeColorPPM(PPMImage* img);

#endif