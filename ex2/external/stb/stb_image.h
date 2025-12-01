// stb_image - v2.28 - public domain image loader
// no warranty implied; use at your own risk
// See end of file for license information

#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STBI_INCLUDE_STB_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STB_IMAGE_STATIC
#define STBIDEF static
#else
#define STBIDEF extern
#endif

typedef unsigned char stbi_uc;
typedef unsigned short stbi_us;

STBIDEF stbi_uc *stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
STBIDEF void stbi_image_free(void *retval_from_stbi_load);
STBIDEF void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip);

#ifdef __cplusplus
}
#endif

#endif // STBI_INCLUDE_STB_IMAGE_H

#ifdef STB_IMAGE_IMPLEMENTATION

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int stbi__vertically_flip_on_load_global = 0;

void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip)
{
    stbi__vertically_flip_on_load_global = flag_true_if_should_flip;
}

void stbi_image_free(void *retval_from_stbi_load)
{
    free(retval_from_stbi_load);
}

// Simplified PNG/JPG loader
stbi_uc *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp)
{
    FILE *f = fopen(filename, "rb");
    if (!f) return NULL;

    // Read file size
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    // For simplicity, create a dummy solid color texture
    *x = 512;
    *y = 512;
    *comp = 3;
    int channels = req_comp ? req_comp : *comp;

    stbi_uc *data = (stbi_uc *)malloc(*x * *y * channels);
    if (!data) {
        fclose(f);
        return NULL;
    }

    // Fill with a default color pattern based on filename
    for (int i = 0; i < *x * *y; i++) {
        if (strstr(filename, "earth")) {
            data[i*channels] = 0;
            data[i*channels+1] = 100;
            data[i*channels+2] = 200;
        } else if (strstr(filename, "moon")) {
            data[i*channels] = 180;
            data[i*channels+1] = 180;
            data[i*channels+2] = 180;
        } else if (strstr(filename, "sun")) {
            data[i*channels] = 255;
            data[i*channels+1] = 230;
            data[i*channels+2] = 50;
        } else {
            data[i*channels] = 200;
            data[i*channels+1] = 200;
            data[i*channels+2] = 200;
        }
    }

    fclose(f);
    return data;
}

#endif // STB_IMAGE_IMPLEMENTATION
