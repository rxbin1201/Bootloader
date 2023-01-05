/*

    tga.h - 02.01.23

*/

#ifndef __TGA_H
#define __TGA_H

#define TGA_SIGNATURE 0x00545047
#define TGA_UNCOMPRESSED_RGB 0x0002

// Import libraries
#include <efi.h>
#include <efilib.h>
#include <stdlib.h>
#include <File/file.h>
#include <Protocols/gop.h>
#include <File/volume.h>

typedef struct {
    UINT8 IdLength;
    UINT8 ColorMapType;
    UINT8 ImageType;
    UINT16 ColorMapOrigin;
    UINT16 ColorMapLength;
    UINT8 ColorMapDepth;
    UINT16 XOrigin;
    UINT16 YOrigin;
    UINT16 Width;
    UINT16 Height;
    UINT8 BitsPerPixel;
    UINT8 ImageDescriptor;
} TGA_HEADER;

UINT32 *TgaParse(unsigned char *ptr, int size);
UINT8 *LoadTgaImage(EFI_HANDLE ImageHandle, CHAR16 *TgaFileName);
VOID DrawTgaImage(UINT8 *FinalTgaBuffer, UINTN TgaImageSize);
EFI_STATUS DrawFinalImageToScreen(EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput, UINT32 *ImageData, UINTN Width, UINTN Height);

#endif // End of file