#ifndef _LIBIMAGE_H_
#define _LIBIMAGE_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

/** Constantes **/

#define O_BINARY 0
#define IO_LEN (1 << 30)
#define MAGIC_PGM "P2\n"
#define MAGIC_PPM "P6\n"

/** Prototypes **/

unsigned char* load_pixmap(char* filename, int* width, int* height);
int load_RGB_pixmap(char* filename, int* width, int* height, unsigned char** R_data, unsigned char** G_data,
    unsigned char** B_data);
void store_pixmap(char* filename, unsigned char* data, int width, int height);
void store_RGB_pixmap(char* filename, unsigned char* R_data, unsigned char* G_data, unsigned char* B_data,
    int width, int height);

#endif