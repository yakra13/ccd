/*18.4 Demonstrate the ability to cross-compile an application for multiple architectures

The makefile contains the cross-compilation logic along with mingw-gcc as the windows compiler
and gcc for linux.


sudo apt-get install gcc-mingw-w64


Was tested under WSL2 using ubuntu on windows.
Will produce executables for linux and windows. When run they will produce bitmap images
that visualize the executables themselves.


./lin-cross
./win-cross.exe


*/
#include "bitmap.h"
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const char* WIN_IN_FILE = "win-cross.exe";
static const char* LIN_IN_FILE = "lin-cross";

#ifdef _WIN32
static const char* WIN_OUT_FILE = "windows-exe.bmp";
static const char* LIN_OUT_FILE = "windows-elf.bmp";
#elif __linux__
static const char* WIN_OUT_FILE = "linux-exe.bmp";
static const char* LIN_OUT_FILE = "linux-elf.bmp";
#endif

bool CreateBitmapFile(const char* filename, PixelData* pixel_data)
{
    FILE* file;
    size_t bytes_written = 0;

    BitmapHeader bmpHeader =
    {
        .type = 0x4D42,
        .size = sizeof(BitmapHeader) + pixel_data->count * 3, //size in bytes of the file
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(BitmapHeader), //start of pixel data
        .dibSize = 40,
        .width = pixel_data->width,
        .height = pixel_data->height,
        .planes = 1,
        .bitCount = 24,
        .compression = 0,
        .imageSize = pixel_data->count * 3,
        .xPPM = 0,
        .yPPM = 0,//2835
        .colorUsed = 0,
        .colorImportant = 0
    };

    if((file = fopen(filename, "wb")) == NULL)
    {
        printf("Could not open %s for writing.\n", filename);
        fclose(file);
        return false;
    }
    else
    {
        fwrite(&bmpHeader, sizeof(bmpHeader), 1, file);
        fwrite(pixel_data->pixels, sizeof(Pixel), pixel_data->count, file);
    }

    fclose(file);
    
    return true;
}

// out_buffer should be checked for NULL and freed after use
long ReadFileBytes(const char* filename, uint8_t** out_buffer)
{
    FILE* file = NULL;
    long file_size = 0;

    if ((file = fopen(filename, "rb")) == NULL)
    {
        perror("Error opening file.\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if((*out_buffer = (uint8_t*)malloc(file_size)) == NULL)
    {
        perror("malloc error\n");
        fclose(file);
        return -1;
    }

    size_t bytes_read = fread(*out_buffer, 1, file_size, file);
    if (bytes_read != file_size)
    {
        perror("Error reading file.\n");
        fclose(file);
        return -1;
    }

    fclose(file);

    return file_size;
}

bool TryTheThing(const char* inFile, const char* outFile)
{
    uint8_t* bytes_buffer = NULL;
    long bytes_read = 0;

    if ((bytes_read = ReadFileBytes(inFile, &bytes_buffer)) == 0)
        return false;

    if (bytes_buffer == NULL)
    {
        printf("Bytes were read but buffer is empty.\n");
        return false;
    }

    int32_t side_length = (int32_t)ceil(sqrt((double)bytes_read));
    uint32_t paddingPerRow = (4 - (side_length * 3) % 4) % 4;

    PixelData pixelData =
    {
        .width = side_length,
        .height = side_length,
        .count = (pixelData.width * pixelData.height) + (paddingPerRow * pixelData.height),
        .pixels = NULL
    };

    pixelData.pixels = (Pixel*)malloc((pixelData.count) * sizeof(Pixel));

    if (pixelData.pixels == NULL)
    {
        printf("Failed to malloc pixel data\n");
        return false;
    }

    int32_t bufferIndex = bytes_read - 1;

    for (int32_t i = pixelData.count - 1; i >= 0; i--)
    {
        uint8_t c = bufferIndex >= 0 ? bytes_buffer[bufferIndex] : 0;

        pixelData.pixels[i].blue = 0;
        pixelData.pixels[i].green = c;
        pixelData.pixels[i].red = 0;

        bufferIndex--;

        if (i % pixelData.width == 0)
        {
            for (int32_t pad = 0; pad < paddingPerRow; pad++)
            {
                pixelData.pixels[i].blue = 0;
                pixelData.pixels[i].green = 0;
                pixelData.pixels[i].red = 0;

                i--;
            }
        }
    }
    
    for (uint32_t i = 0; i < pixelData.count; i++)
    {
        uint8_t c = i < (uint32_t)bytes_read ? bytes_buffer[i] : 0;

        pixelData.pixels[i].blue = 0;
        pixelData.pixels[i].green = c;
        pixelData.pixels[i].red = 0;
    }

    if (CreateBitmapFile(outFile, &pixelData) == false)
    {
        printf("Failed to make file\n");
        free(pixelData.pixels);
        return false;
    }

    free(pixelData.pixels);

    return true;
}

int32_t main()
{
    if (TryTheThing(LIN_IN_FILE, LIN_OUT_FILE) == false)
        return EXIT_FAILURE;

    if (TryTheThing(WIN_IN_FILE, WIN_OUT_FILE) == false)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}