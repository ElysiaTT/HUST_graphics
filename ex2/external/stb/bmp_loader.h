#ifndef BMP_LOADER_H
#define BMP_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
} BMPHeader;

typedef struct {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    unsigned int colorsUsed;
    unsigned int colorsImportant;
} BMPInfoHeader;
#pragma pack(pop)

unsigned char* loadBMP(const char* filename, int* width, int* height, int* channels) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    // Read BMP header
    BMPHeader header;
    fread(&header.type, sizeof(unsigned short), 1, file);
    fread(&header.size, sizeof(unsigned int), 1, file);
    fread(&header.reserved1, sizeof(unsigned short), 1, file);
    fread(&header.reserved2, sizeof(unsigned short), 1, file);
    fread(&header.offset, sizeof(unsigned int), 1, file);

    // Check if it's a BMP file
    if (header.type != 0x4D42) { // 'BM' in little endian
        printf("Error: Not a BMP file\n");
        fclose(file);
        return NULL;
    }

    // Read Info Header
    BMPInfoHeader infoHeader;
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    *width = infoHeader.width;
    *height = infoHeader.height;
    *channels = infoHeader.bitsPerPixel / 8;

    // Move to pixel data
    fseek(file, header.offset, SEEK_SET);

    // Calculate row size (must be multiple of 4)
    int rowSize = ((*width) * (*channels) + 3) & ~3;
    int dataSize = rowSize * abs(*height);

    unsigned char* data = (unsigned char*)malloc(dataSize);
    if (!data) {
        printf("Error: Cannot allocate memory\n");
        fclose(file);
        return NULL;
    }

    // Read pixel data
    fread(data, 1, dataSize, file);
    fclose(file);

    // BMP is stored bottom-to-top, so flip it
    if (*height > 0) {
        int actualRowSize = (*width) * (*channels);
        unsigned char* flipped = (unsigned char*)malloc(dataSize);
        for (int y = 0; y < *height; y++) {
            memcpy(flipped + y * actualRowSize,
                   data + (*height - 1 - y) * rowSize,
                   actualRowSize);
        }
        free(data);
        data = flipped;
    } else {
        *height = -(*height);
    }

    // Convert BGR to RGB
    if (*channels >= 3) {
        for (int i = 0; i < (*width) * (*height); i++) {
            unsigned char temp = data[i * (*channels)];
            data[i * (*channels)] = data[i * (*channels) + 2];
            data[i * (*channels) + 2] = temp;
        }
    }

    return data;
}

void freeBMP(unsigned char* data) {
    if (data) {
        free(data);
    }
}

#endif // BMP_LOADER_H
