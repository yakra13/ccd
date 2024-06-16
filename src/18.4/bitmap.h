#pragma once
#include <stdbool.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
    uint32_t dibSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPPM;
    int32_t yPPM;
    uint32_t colorUsed;
    uint32_t colorImportant;
} BitmapHeader;

typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;

typedef struct
{
    int32_t width;
    int32_t height;
    uint32_t count;
    Pixel* pixels;
} PixelData;
#pragma pack(pop)

bool CreateBitmapFile(const char* filename, PixelData* pixel_data);